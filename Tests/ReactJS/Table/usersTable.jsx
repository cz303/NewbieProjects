import React from "react";

export class Users extends React.Component {
  constructor() {
    super();
    this.state = {
      error: null,
      users: [],
      page: 1,
      rowPerPage: 15,
      selected: null,
      filtering: false,
      originalUsers: [],
      countUsers: 0,
      rows: -1,
      sort: { direction: "desc", field: "" }
    };
  }

  changeRows(e) {
    const field = document.getElementById("rowField");
    const rows = parseInt(field.value, 10);

    if (!isNaN(rows)) {
      if (rows < 0) {
        alert("Нельзя указать отрицательное число!");
        return;
      }
    } else {
      alert("Это не похоже на число");
      return;
    }
    this.setState({
      rows: rows
    });
  }

  init() {
    return (
      <div id="content">
        <p>Выберите количество записей (32 - мало, 1000 - много)</p>
        <input
          type="text"
          id="rowField"
          className="rowField"
          defaultValue="32"
        />
        <button onClick={this.changeRows.bind(this)}>Start</button>
      </div>
    );
  }

  request() {
    const rows = this.state.rows;
    fetch(
      `http://www.filltext.com/?rows=${rows}&id=%7Bnumber%7C1000%7D&firstName=%7BfirstName%7D&lastName=%7BlastName%7D&email=%7Bemail%7D&phone=%7Bphone%7C(xxx)xxx-xx-xx%7D&address=%7BaddressObject%7D&description=%7Blorem%7C32%7D`
    )
      .then(res => res.json())
      .then(
        result => {
          this.setState({
            users: result,
            originalUsers: result,
            countUsers: result.length
          });
        },
        error => {
          this.setState({
            error
          });
          console.log(error);
        }
      );
  }

  check(obj, search) {
    for (const key of Object.keys(obj)) {
      if (typeof obj[key] === "object") {
        return this.check(obj[key], search);
      }
      if (typeof obj[key] === "string") {
        if (obj[key].indexOf(search) > -1) {
          return true;
        }
      }
      if (typeof obj[key] === "number") {
        if (obj[key].toString().indexOf(search) > -1) {
          return true;
        }
      }
    }
    return false;
  }

  onSearchClickHandler() {
    const field = document.getElementById("searchField");
    this.findUsers(field.value);
  }

  findUsers(search) {
    let originalUsers;
    if (this.state.originalUsers.length === 0)
      originalUsers = JSON.parse(JSON.stringify(this.state.users));
    else originalUsers = JSON.parse(JSON.stringify(this.state.originalUsers));

    this.setState({ filtering: true, selected: null, originalUsers, page: 1 });

    if (search === "") {
      this.setState({
        users: originalUsers,
        filtering: false,
        countUsers: originalUsers.length,
        originalUsers: originalUsers,
        sort: { direction: "desc", field: "" }
      });
    } else {
      const found = originalUsers.filter(user => this.check(user, search));

      this.setState({
        users: found,
        originalUsers,
        filtering: false,
        countUsers: found.length
      });
    }
  }

  listUsers() {
    const rt = [];

    for (
      let index = (this.state.page - 1) * this.state.rowPerPage;
      index < this.state.page * this.state.rowPerPage;
      index++
    ) {
      if (index < this.state.countUsers) {
        rt.push(
          <tr
            key={index}
            data-id={index}
            className={
              parseInt(this.state.selected, 10) === index ? "active" : ""
            }
            onClick={this.onRowClickHandler.bind(this)}
          >
            <td>{this.state.users[index].id}</td>
            <td>{this.state.users[index].firstName}</td>
            <td>{this.state.users[index].lastName}</td>
            <td>{this.state.users[index].email}</td>
            <td>{this.state.users[index].phone}</td>
          </tr>
        );
      }
    }
    return rt;
  }

  getFullInfo(index) {
    if (this.state.selected != null) {
      return (
        <div id="description">
          <p>
            {" "}
            Выбран пользователь{" "}
            <b>
              {`${this.state.users[index].firstName} ${
                this.state.users[index].lastName
              }`}
            </b>{" "}
          </p>
          Описание:
          <textarea value={this.state.users[index].description} readOnly />
          <p>
            Адрес проживания:{" "}
            <b>{this.state.users[index].address.streetAddress}</b> <br />
            Город: <b>{this.state.users[index].address.city}</b> <br />
            Провинция/штат: <b>{this.state.users[index].address.state}</b>{" "}
            <br />
            Индекс: <b>{this.state.users[index].address.zip}</b> <br />
          </p>
        </div>
      );
    }
    return <div>Пользователь не выбран</div>;
  }

  onRowClickHandler(e) {
    e.stopPropagation();
    if (this.state.selected !== e.currentTarget.dataset.id) {
      const userCard = document.getElementById("description");
      if (userCard !== null) {
        if (userCard.classList.contains("fade"))
          userCard.classList.remove("fade");

        setTimeout(function() {
          userCard.classList.add("fade");
        }, 1);
      }
      var ctx = this;
      const id = e.currentTarget.dataset.id;
      setTimeout(function() {
        ctx.setState({ selected: id });
      }, 150);
    }
  }

  pageLinks() {
    const rt = [];
    if (this.state.countUsers !== 0) {
      if (this.state.page + 5 > 8) {
        rt.push(
          <a
            key="back"
            data-page="back"
            onClick={this.onPageClickHandler.bind(this)}
          >
            &laquo;
          </a>
        );
      }

      for (
        let index = this.state.page - 2;
        index < this.state.page - 2 + 5;
        index++
      ) {
        if (
          index <= Math.ceil(this.state.countUsers / this.state.rowPerPage) &&
          index > 0
        ) {
          rt.push(
            <a
              key={index}
              onClick={this.onPageClickHandler.bind(this)}
              className={this.state.page === index ? "active" : ""}
              data-page={index}
            >
              {" "}
              {index}{" "}
            </a>
          );
        }
      }

      if (
        this.state.page - 2 <=
        Math.ceil(this.state.countUsers / this.state.rowPerPage) - 5
      ) {
        rt.push(
          <a
            key="forward"
            data-page="forward"
            onClick={this.onPageClickHandler.bind(this)}
          >
            &raquo;
          </a>
        );
      }
      return rt;
    }
  }

  onPageClickHandler(e) {
    e.stopPropagation();
    this.setState({ selected: null });
    let newPage;
    switch (e.currentTarget.dataset.page) {
      case "forward":
        for (
          let index = this.state.page;
          index < this.state.page + 5;
          index++
        ) {
          if (
            index <= Math.ceil(this.state.users.length / this.state.rowPerPage)
          ) {
            newPage = index;
          }
        }
        this.setState({
          page: newPage
        });
        break;
      case "back":
        for (
          let index = this.state.page;
          index > this.state.page - 5;
          index--
        ) {
          if (index > 0) {
            newPage = index;
          }
        }
        this.setState({
          page: newPage
        });
        break;
      default:
        this.setState({
          page: parseInt(e.currentTarget.dataset.page, 10)
        });
        break;
    }
  }

  onTitleClickHandler(e) {
    if (e.target.tagName === "TH") {
      e.preventDefault();
      let dir, templUsers;

      templUsers = JSON.parse(JSON.stringify(this.state.users));
      this.setState({ filtering: true, selected: null });

      if (this.state.sort.field === e.target.dataset.type)
        this.state.sort.direction === "desc" ? (dir = "asc") : (dir = "desc");
      else dir = "desc";

      if (dir === "desc") {
        templUsers.sort((a, b) => {
          if (a[e.target.dataset.type] < b[e.target.dataset.type]) return -1;
          if (a[e.target.dataset.type] > b[e.target.dataset.type]) return 1;
          return 0;
        });
      }
      if (dir === "asc") {
        templUsers.sort((a, b) => {
          if (a[e.target.dataset.type] > b[e.target.dataset.type]) return -1;
          if (a[e.target.dataset.type] < b[e.target.dataset.type]) return 1;
          return 0;
        });
      }

      this.setState({
        filtering: false,
        users: templUsers,
        sort: { direction: dir, field: e.target.dataset.type }
      });
    }
  }

  render() {
    if (this.state.error) {
      return (
        <div id="content">
          Error:
          {this.state.error.message}
        </div>
      );
    }

    if (this.state.rows === -1) return <div id="content">{this.init()}</div>;

    if (this.state.originalUsers.length === 0) this.request();

    return (
      <div id="content">
        <div>
          Users:
          {this.state.countUsers}
        </div>
        {this.state.users.length !== 0 ||
        this.state.originalUsers.length !== 0 ? (
          <div>
            <input
              type="text"
              id="searchField"
              className="searchField"
              defaultValue=""
            />
            <button onClick={this.onSearchClickHandler.bind(this)}>
              Search
            </button>
          </div>
        ) : (
          <div />
        )}
        <table id="usersList">
          <thead onClick={this.onTitleClickHandler.bind(this)}>
            <tr>
              <th
                data-type="id"
                className={
                  this.state.sort.field === "id"
                    ? this.state.sort.direction
                    : ""
                }
              >
                ID
              </th>
              <th
                data-type="firstName"
                className={
                  this.state.sort.field === "firstName"
                    ? this.state.sort.direction
                    : ""
                }
              >
                First Name
              </th>
              <th
                data-type="lastName"
                className={
                  this.state.sort.field === "lastName"
                    ? this.state.sort.direction
                    : ""
                }
              >
                Last Name
              </th>
              <th
                data-type="email"
                className={
                  this.state.sort.field === "email"
                    ? this.state.sort.direction
                    : ""
                }
              >
                Email
              </th>
              <th
                data-type="phone"
                className={
                  this.state.sort.field === "phone"
                    ? this.state.sort.direction
                    : ""
                }
              >
                Phone{" "}
              </th>
            </tr>
          </thead>
          <tfoot>
            <tr>
              <td colSpan="5">
                <div className="links">{this.pageLinks()}</div>
              </td>
            </tr>
          </tfoot>
          <tbody>
            {(this.state.users.length !== 0 ||
              this.state.originalUsers.length !== 0) &&
            !this.state.filtering ? (
              this.listUsers()
            ) : (
              <tr>
                <td colSpan="5" className="loading">
                  <div className="windows8">
                    <div className="wBall" id="wBall_1">
                      <div className="wInnerBall" />
                    </div>
                    <div className="wBall" id="wBall_2">
                      <div className="wInnerBall" />
                    </div>
                    <div className="wBall" id="wBall_3">
                      <div className="wInnerBall" />
                    </div>
                    <div className="wBall" id="wBall_4">
                      <div className="wInnerBall" />
                    </div>
                    <div className="wBall" id="wBall_5">
                      <div className="wInnerBall" />
                    </div>
                  </div>
                </td>
              </tr>
            )}
          </tbody>
        </table>
        {this.getFullInfo(this.state.selected)}
      </div>
    );
  }
}
