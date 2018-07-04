package main

import (
	"encoding/json"
	"encoding/xml"
	"fmt"
	"io"
	"net/http"
	"net/http/httptest"
	"os"
	"strconv"
	"strings"
	"testing"
	"time"
)

type XmlUser struct {
	Id        int    `xml:"id"`
	FirstName string `xml:"first_name"`
	LastName  string `xml:"last_name"`
	Age       int    `xml:"age"`
	About     string `xml:"about"`
	Gender    string `xml:"gender"`
}

func SearchServer(users *[]User, req *SearchRequest) error {

	xmlFile, err := os.Open("dataset.xml")
	if err != nil {
		fmt.Println("Error opening file:", err)
		return err
	}
	defer xmlFile.Close()

	decoder := xml.NewDecoder(xmlFile)
	user := XmlUser{}
	for {
		tok, tokenErr := decoder.Token()
		if tokenErr != nil && tokenErr != io.EOF {
			fmt.Println("error happend", tokenErr)
			return tokenErr
		} else if tokenErr == io.EOF {
			break
		}
		if tok == nil {
			fmt.Println("t is nil break")
		}
		switch tok := tok.(type) {
		case xml.StartElement:
			if tok.Name.Local == "row" {
				valid := false
				decoder.DecodeElement(&user, &tok)
				if req.Query != "" {
					if strings.Contains(user.FirstName+" "+user.LastName, req.Query) || strings.Contains(user.About, req.Query) {
						valid = true
					}
				} else {
					valid = true
				}
				if valid {
					*users = append(*users, User{user.Id, user.FirstName + " " + user.LastName, user.Age, user.About, user.Gender})
				}
			}
		}
	}

	return nil
}

func contains(s []string, e string) bool {
	for _, a := range s {
		if a == e {
			return true
		}
	}
	return false
}

func ParseReq(w http.ResponseWriter, r *http.Request) {
	req := SearchRequest{}
	req.OrderField = r.FormValue("order_field")
	req.Limit, _ = strconv.Atoi(r.FormValue("limit"))
	req.Offset, _ = strconv.Atoi(r.FormValue("offset"))
	req.OrderBy, _ = strconv.Atoi(r.FormValue("order_by"))
	req.Query = r.FormValue("query")

	if r.Header.Get("AccessToken") == "errorDb" {
		w.WriteHeader(http.StatusInternalServerError)
		io.WriteString(w, `{"status": 500, "err": "StatusInternalServerError"}`)
		return
	}

	if r.Header.Get("AccessToken") == "ErrJson" {
		w.WriteHeader(http.StatusBadRequest)
		io.WriteString(w, `{"status": 401, "err": Unauthorized}`)
		return
	}

	if r.Header.Get("AccessToken") == "ErrUnknown" {
		w.WriteHeader(http.StatusBadRequest)
		io.WriteString(w, `{"status": 400, "Error": "unknownTestError"}`)
		return
	}

	if r.Header.Get("AccessToken") == "wrongRespJson" {
		w.WriteHeader(http.StatusOK)
		io.WriteString(w, `{"status": 200, "foo": "bar"}`)
		return
	}

	if r.Header.Get("AccessToken") == "ServerError" {
		w.WriteHeader(http.StatusInternalServerError)
		io.WriteString(w, `{"status": 500, "err": "Server Error"}`)
		return
	}

	if r.Header.Get("AccessToken") == "ServerTimeOut" {
		time.Sleep(2 * time.Second)
		w.WriteHeader(http.StatusInternalServerError)
		io.WriteString(w, `{"status": 500, "err": "Server Error"}`)
		return
	}

	if r.Header.Get("AccessToken") != "testToken" {
		w.WriteHeader(http.StatusUnauthorized)
		io.WriteString(w, `{"status": 401, "err": "Unauthorized"}`)
		return
	}

	if req.OrderField == "" {
		req.OrderField = "Name"
	} else {
		if !(contains([]string{"Name", "Id", "Age"}, req.OrderField)) {
			w.WriteHeader(http.StatusBadRequest)
			io.WriteString(w, `{"status": 400, "Error": "ErrorBadOrderField"}`)
			return
		}
	}

	users := make([]User, 0)
	SearchServer(&users, &req)
	jsonMarshal, _ := json.Marshal(users)
	w.WriteHeader(http.StatusOK)
	io.WriteString(w, string(jsonMarshal))
}

func TestSearchServer_Query(t *testing.T) {
	result := ""
	ts := httptest.NewServer(http.HandlerFunc(ParseReq))
	defer ts.Close()
	testClient := SearchClient{"testToken", ts.URL}

	expecting := `[0] Boyd Wolf
[5] Beulah Stark
[6] Jennings Mays
[7] Leann Travis
[8] Glenn Jordan
[11] Gilmore Guerra
[12] Cruz Guerrero
[20] Lowery York
[23] Gates Spencer
`

	testReq := SearchRequest{9, 0, "Lorem", "Name", 0}
	resp, err := testClient.FindUsers(testReq)

	for _, user := range resp.Users {
		result += fmt.Sprintf("[%v] %v\n", user.Id, user.Name)
	}

	if expecting != result {
		t.Errorf("Result not match")
		fmt.Println("Got \n", result)
		fmt.Println("Await \n", expecting)
	}

	testReq = SearchRequest{26, 0, "", "", 0}
	resp, err = testClient.FindUsers(testReq)

	if err != nil {
		t.Errorf("error: %s", err)
	}

}

func TestSearchServer_BadRequest(t *testing.T) {
	ts := httptest.NewServer(http.HandlerFunc(ParseReq))
	defer ts.Close()
	testClient := SearchClient{"testToken", ts.URL}

	testReq := SearchRequest{1, 0, "", "Gender", 0}
	_, err := testClient.FindUsers(testReq)
	if err.Error() != "OrderFeld Gender invalid" {
		t.Errorf("Await '%s', but have: %s", "OrderFeld Gender invalid", err)
	}

	testClient = SearchClient{"ErrJson", ts.URL}
	_, err = testClient.FindUsers(testReq)
	if err.Error() != "cant unpack error json: invalid character 'U' looking for beginning of value" {
		t.Errorf("Await '%s', but have: %s", "cant unpack error json: invalid character 'U' looking for beginning of value", err)
	}

	testClient = SearchClient{"ErrUnknown", ts.URL}
	_, err = testClient.FindUsers(testReq)
	if err.Error() != "unknown bad request error: unknownTestError" {
		t.Errorf("Await '%s', but have: %s", "unknown bad request error: unknownTestError", err)
	}

}

func TestSearchServer_WrongToken(t *testing.T) {
	ts := httptest.NewServer(http.HandlerFunc(ParseReq))
	defer ts.Close()

	testClient := SearchClient{"testWrongToken", ts.URL}
	testReq := SearchRequest{1, 0, "", "Gender", 0}
	_, err := testClient.FindUsers(testReq)

	if err.Error() != "Bad AccessToken" {
		t.Errorf("Await '%s', but have: %s", "Bad AccessToken", err)
	}

}

func TestSearchServer_WrongQuery(t *testing.T) {
	ts := httptest.NewServer(http.HandlerFunc(ParseReq))
	defer ts.Close()

	testReq := SearchRequest{1, 0, "", "", 0}
	testClient := SearchClient{"wrongRespJson", ts.URL}
	_, err := testClient.FindUsers(testReq)
	if err.Error() != "cant unpack result json: json: cannot unmarshal object into Go value of type []main.User" {
		t.Errorf("Await '%s', but have: %s", "cant unpack result json: json: cannot unmarshal object into Go value of type []main.User", err)
	}

	testClient = SearchClient{"ServerError", ts.URL}
	_, err = testClient.FindUsers(testReq)
	if err.Error() != "SearchServer fatal error" {
		t.Errorf("Await '%s', but have: %s", "SearchServer fatal error", err)
	}

}

func TestSearchServer_LimitAndOffset(t *testing.T) {
	ts := httptest.NewServer(http.HandlerFunc(ParseReq))
	defer ts.Close()
	testClient := SearchClient{"testToken", ts.URL}

	testReq := SearchRequest{-1, 0, "", "", 0}
	_, err := testClient.FindUsers(testReq)
	if err.Error() != "limit must be > 0" {
		t.Errorf("Await '%s', but have: %s", "limit must be > 0", err)
	}

	testReq = SearchRequest{1, -1, "", "", 0}
	_, err = testClient.FindUsers(testReq)
	if err.Error() != "offset must be > 0" {
		t.Errorf("Await '%s', but have: %s", "offset must be > 0", err)
	}

}

func TestSearchServer_WrongServer(t *testing.T) {
	ts := httptest.NewServer(http.HandlerFunc(ParseReq))

	testClient := SearchClient{"unknownError", ts.URL + "2715&??:"}
	testReq := SearchRequest{1, 0, ":关闭", "//&?//", 0}
	_, err := testClient.FindUsers(testReq)
	if err == nil {
		t.Errorf("Await error, but have nil")
	}

	testClient = SearchClient{"ServerTimeOut", ts.URL}
	_, err = testClient.FindUsers(testReq)
	if err == nil {
		t.Errorf("Await error, but have nil")
	}

	ts.Close()
}
