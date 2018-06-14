package main

import (
	"bufio"
	"bytes"
	"fmt"
	"io"
	"io/ioutil"
	"os"
)

func main() {
	out := bytes.NewBuffer(nil)
	input := bufio.NewScanner(os.Stdin)

	dir, err := os.Getwd()
	if err != nil {
		panic(err.Error())
	}
	err = dirTree(out, dir+string(os.PathSeparator)+".")
	if err != nil {
		panic(err.Error())
	}

	// Пишем буфер в stdout
	fmt.Printf("%v\n", out.String())

	if len(os.Args) == 1 {
		fmt.Println("Save to file? <y/n>: ")
		input.Scan()
		if input.Text() == "y" {
			os.Args = append(os.Args, "-f")
		} else {
			os.Exit(0)
		}
	}

	if contains(os.Args, "-f") {
		// Пишем буфер в файл
		w, err := os.Create("output.txt")
		if err != nil {
			panic(err)
		}
		defer w.Close()

		n, err := io.Copy(w, out)
		if err != nil {
			panic(err)
		}

		fmt.Printf("Writted %v bytes in %v\n", n, dir+string(os.PathSeparator)+"output.txt")
	}

	fmt.Println("Press enter to exit...")
	input.Scan()
}

// Получаем список и пишем его в буфер
func dirTree(output io.Writer, path string) error {
	list := make([]string, 0, 50)
	megaPrefix := ""

	getList(&list, path, &megaPrefix)

	for _, p := range list {
		fmt.Fprintf(output, "%s\n", p)
	}

	return nil
}

// Получаем отформатированный список папок
func getList(list *[]string, rootpath string, megaPrefix *string) {
	prefix := ""
	del := 1

	files, _ := ioutil.ReadDir(rootpath)

	for i, file := range files {
		switch {
		case lastDir(files[i+1:]):
			prefix = "└───"
		case i != len(files)-1:
			prefix = "├───"
		}
		if !file.IsDir() || (countFiles(files) > 2 && len(*megaPrefix) != 0) {
			continue
		}

		*list = append(*list, *megaPrefix+prefix+file.Name())

		if file.IsDir() {
			switch {
			case lastDir(files[i+1:]):
				*megaPrefix = *megaPrefix + "\t"
				del = 1
			case i != len(files)-1:
				*megaPrefix = *megaPrefix + "│" + "\t"
				del = 4
			}
			getList(list, rootpath+string(os.PathSeparator)+file.Name(), megaPrefix)
			*megaPrefix = (*megaPrefix)[:len(*megaPrefix)-del]
		}
	}
}

func countFiles(files []os.FileInfo) int {
	result := 0
	for _, file := range files {
		if !file.IsDir() {
			result++
		}
	}
	return result
}

func lastDir(files []os.FileInfo) bool {
	for _, file := range files {
		if file.IsDir() {
			return false
		}
	}
	return true
}

func contains(strSlice []string, search string) bool {
	for _, value := range strSlice {
		if value == search {
			return true
		}
	}
	return false
}
