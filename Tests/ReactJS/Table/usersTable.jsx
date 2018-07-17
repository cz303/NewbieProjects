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

    if (this.state.originalUsers.length === 0) {
      this.request();
      return <Idle />;
    }

    return <UserTable handler={this} />;
  }
}

class UserTable extends React.Component {
  listUsers() {
    const rt = [];

    for (
      let index =
        (this.props.handler.state.page - 1) *
        this.props.handler.state.rowPerPage;
      index <
      this.props.handler.state.page * this.props.handler.state.rowPerPage;
      index++
    ) {
      if (index < this.props.handler.state.countUsers) {
        let foundTip = [];
        if (this.props.handler.state.users[index].hasOwnProperty("___found")) {
          this.props.handler.state.users[index].___found.forEach(element => {
            foundTip.push(
              <span>
                {" "}
                {element.in}: {element.matchBefore}
                <b>{element.search}</b>
                {element.matchAfter}
              </span>
            );
          });
        }

        rt.push(
          <tr
            key={index}
            data-id={index}
            className={
              parseInt(this.props.handler.state.selected, 10) === index
                ? "active"
                : ""
            }
            onClick={this.onRowClickHandler.bind(this)}
          >
            <td>
              {foundTip.length > 0 ? (
                <div className="tooltip">
                  <span className="tooltiptext">{foundTip} </span>
                </div>
              ) : (
                ""
              )}
              {this.props.handler.state.users[index].id}
            </td>
            <td>{this.props.handler.state.users[index].firstName}</td>
            <td>{this.props.handler.state.users[index].lastName}</td>
            <td>{this.props.handler.state.users[index].email}</td>
            <td>{this.props.handler.state.users[index].phone}</td>
          </tr>
        );
      }
    }
    return rt;
  }

  getFullInfo(index) {
    if (this.props.handler.state.selected != null) {
      return (
        <div id="description">
          <p>
            {" "}
            Выбран пользователь{" "}
            <b>
              {`${this.props.handler.state.users[index].firstName} ${
                this.props.handler.state.users[index].lastName
              }`}
            </b>{" "}
          </p>
          Описание:
          <textarea
            value={this.props.handler.state.users[index].description}
            readOnly
          />
          <p>
            Адрес проживания:{" "}
            <b>{this.props.handler.state.users[index].address.streetAddress}</b>{" "}
            <br />
            Город: <b>
              {this.props.handler.state.users[index].address.city}
            </b>{" "}
            <br />
            Провинция/штат:{" "}
            <b>{this.props.handler.state.users[index].address.state}</b> <br />
            Индекс: <b>
              {this.props.handler.state.users[index].address.zip}
            </b>{" "}
            <br />
          </p>
        </div>
      );
    }
    return <div>Пользователь не выбран</div>;
  }

  onRowClickHandler(e) {
    e.stopPropagation();
    if (this.props.handler.state.selected !== e.currentTarget.dataset.id) {
      const userCard = document.getElementById("description");
      if (userCard !== null) {
        if (userCard.classList.contains("fade"))
          userCard.classList.remove("fade");

        setTimeout(function() {
          userCard.classList.add("fade");
        }, 1);
      }
      var ctx = this.props.handler;
      const id = e.currentTarget.dataset.id;
      setTimeout(function() {
        ctx.setState({ selected: id });
      }, 150);
    }
  }

  onTitleClickHandler(e) {
    if (e.target.tagName === "TH") {
      e.preventDefault();
      let dir, templUsers;

      templUsers = JSON.parse(JSON.stringify(this.props.handler.state.users));
      this.props.handler.setState({ filtering: true, selected: null });

      if (this.props.handler.state.sort.field === e.target.dataset.type)
        this.props.handler.state.sort.direction === "desc"
          ? (dir = "asc")
          : (dir = "desc");
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

      this.props.handler.setState({
        filtering: false,
        users: templUsers,
        sort: { direction: dir, field: e.target.dataset.type }
      });
    }
  }

  render() {
    return (
      <div id="content">
        {this.props.handler.state.users.length !== 0 ||
        this.props.handler.state.originalUsers.length !== 0 ? (
          <Search handler={this.props.handler} />
        ) : (
          <div />
        )}
        <table id="usersList">
          <thead onClick={this.onTitleClickHandler.bind(this)}>
            <tr>
              <th
                data-type="id"
                className={
                  this.props.handler.state.sort.field === "id"
                    ? this.props.handler.state.sort.direction
                    : ""
                }
              >
                ID
              </th>
              <th
                data-type="firstName"
                className={
                  this.props.handler.state.sort.field === "firstName"
                    ? this.props.handler.state.sort.direction
                    : ""
                }
              >
                First Name
              </th>
              <th
                data-type="lastName"
                className={
                  this.props.handler.state.sort.field === "lastName"
                    ? this.props.handler.state.sort.direction
                    : ""
                }
              >
                Last Name
              </th>
              <th
                data-type="email"
                className={
                  this.props.handler.state.sort.field === "email"
                    ? this.props.handler.state.sort.direction
                    : ""
                }
              >
                Email
              </th>
              <th
                data-type="phone"
                className={
                  this.props.handler.state.sort.field === "phone"
                    ? this.props.handler.state.sort.direction
                    : ""
                }
              >
                Phone{" "}
              </th>
            </tr>
          </thead>
          <tbody>
            {(this.props.handler.state.users.length !== 0 ||
              this.props.handler.state.originalUsers.length !== 0) &&
            !this.props.handler.state.filtering ? (
              this.listUsers()
            ) : (
              <tr>
                <td colSpan="5" className="loading">
                  <Idle />
                </td>
              </tr>
            )}
          </tbody>
          <tfoot>
            <tr>
              <td colSpan="5">
                <PageNavigation handler={this.props.handler} />
              </td>
            </tr>
          </tfoot>
        </table>
        {this.getFullInfo(this.props.handler.state.selected)}
      </div>
    );
  }
}

class Idle extends React.Component {
  render() {
    return (
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
    );
  }
}

class PageNavigation extends React.Component {
  onPageClickHandler(e) {
    e.stopPropagation();
    this.props.handler.setState({ selected: null });
    let newPage;
    switch (e.currentTarget.dataset.page) {
      case "forward":
        for (
          let index = this.props.handler.state.page;
          index < this.props.handler.state.page + 5;
          index++
        ) {
          if (
            index <=
            Math.ceil(
              this.props.handler.state.users.length /
                this.props.handler.state.rowPerPage
            )
          ) {
            newPage = index;
          }
        }
        this.props.handler.setState({
          page: newPage
        });
        break;
      case "back":
        for (
          let index = this.props.handler.state.page;
          index > this.props.handler.state.page - 5;
          index--
        ) {
          if (index > 0) {
            newPage = index;
          }
        }
        this.props.handler.setState({
          page: newPage
        });
        break;
      default:
        this.props.handler.setState({
          page: parseInt(e.currentTarget.dataset.page, 10)
        });
        break;
    }
  }

  pageLinks() {
    const rt = [];
    if (this.props.handler.state.countUsers !== 0) {
      if (this.props.handler.state.page + 5 > 8) {
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
        let index = this.props.handler.state.page - 2;
        index < this.props.handler.state.page - 2 + 5;
        index++
      ) {
        if (
          index <=
            Math.ceil(
              this.props.handler.state.countUsers /
                this.props.handler.state.rowPerPage
            ) &&
          index > 0
        ) {
          rt.push(
            <a
              key={index}
              onClick={this.onPageClickHandler.bind(this)}
              className={
                this.props.handler.state.page === index ? "active" : ""
              }
              data-page={index}
            >
              {" "}
              {index}{" "}
            </a>
          );
        }
      }

      if (
        this.props.handler.state.page - 2 <=
        Math.ceil(
          this.props.handler.state.countUsers /
            this.props.handler.state.rowPerPage
        ) -
          5
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

  render() {
    return (
      <div className="links">
        {" "}
        {this.pageLinks()}
        <div>Users: {this.props.handler.state.countUsers}</div>
      </div>
    );
  }
}

class Search extends React.Component {
  check(originalObj, obj, search) {
    for (const key of Object.keys(obj)) {
      if (typeof obj[key] === "object") {
        return this.check(obj, obj[key], search);
      }
      if (typeof obj[key] === "string" || typeof obj[key] === "number") {
        let index = obj[key].toString().indexOf(search);
        if (index > -1) {
          let regex = new RegExp("([^| ])*" + search + "*([^| ]+)", "i");
          let substr = obj[key].match(regex)[0];
          if (!originalObj.hasOwnProperty("___found"))
            originalObj.___found = [];
          originalObj.___found.push({
            in: key,
            matchBefore: substr.substring(0, index),
            matchAfter: substr.substring(index + search.length, substr.length),
            search: search
          });
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

  onResetClickHandler() {
    const field = document.getElementById("searchField");
    field.value = "";
    this.findUsers("");
  }

  findUsers(search) {
    let originalUsers;
    if (this.props.handler.state.originalUsers.length === 0)
      originalUsers = JSON.parse(
        JSON.stringify(this.props.handler.state.users)
      );
    else
      originalUsers = JSON.parse(
        JSON.stringify(this.props.handler.state.originalUsers)
      );

    this.props.handler.setState({
      filtering: true,
      selected: null,
      originalUsers,
      page: 1
    });

    if (search === "") {
      this.props.handler.setState({
        users: originalUsers,
        filtering: false,
        countUsers: originalUsers.length,
        originalUsers: originalUsers,
        sort: { direction: "desc", field: "" }
      });
    } else {
      const found = this.props.handler.state.users.filter(user =>
        this.check(user, user, search)
      );

      this.props.handler.setState({
        users: found,
        originalUsers,
        filtering: false,
        countUsers: found.length
      });
    }
  }

  render() {
    return (
      <div>
        <input
          type="text"
          id="searchField"
          className="searchField"
          defaultValue=""
        />
        <button onClick={this.onSearchClickHandler.bind(this)}>Search</button>
        {this.props.handler.state.countUsers <
        this.props.handler.state.originalUsers.length ? (
          <button onClick={this.onResetClickHandler.bind(this)}>Clear</button>
        ) : (
          ""
        )}
      </div>
    );
  }
}
