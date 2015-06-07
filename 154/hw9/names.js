/* Stefan Dierauf May 2014
js file for baby names
datalist autocomplete added
*/


"use strict";

(function() {
  
  var BABY_API_URL = "https://webster.cs.washington.edu/cse154/babynames.php"; 
  
  window.onload = function() {
    ajaxify("?type=list", enableAndPopulateNames);
    document.getElementById("search").onclick = search;
    
  };
  
  //Gets the list of names from the server and fills the select with them
  function enableAndPopulateNames() {
    if (this.status == 200) {
      var names = this.responseText.split("\n");
      var namesList = document.getElementById("allnameslist");
      for (var i = 0; i < names.length; i++) {
        var opt = document.createElement("option");
        opt.setAttribute("value", names[i]);
        opt.innerHTML = names[i];
        namesList.appendChild(opt);
      }
      document.getElementById("allnames").disabled = false;
      stripLoader("namearea");
    } else {
      fail(this.status);
    }
    
  }
  
  //Megafunction that calls all the necessary functions after a search
  function search() {
    reset();
    findMeaning(); //i had to.
    findRank();
    findCelebs();
  }
  
  //resets the necessary parts of the page
  function reset() {
    document.getElementById("resultsarea").style.display = "";
    document.getElementById("meaning").innerHTML = "";
    document.getElementById("graph").innerHTML = "";
    document.getElementById("norankdata").style.display = "none";
    document.getElementById("celebs").innerHTML = "";
    document.getElementById("norankdata").style.display = "none";
    document.getElementById("errors").innerHTML = "";
    showSpinnies(true);
  }
  
  //Displays error div mit deutschmacht
  function fail(errorCode) {
    var errors = document.getElementById("errors");
    var warning = document.createElement("p");
    warning.innerHTML = "ACHTUNG! Etwas ist schiefgelaufen (Fehlercode: " + 
        errorCode + ")\n";
    errors.appendChild(warning);
    errors.style.display = "";
    //There is intentionally bad style in the following lines of code.
    //Be nice pls
    if (!document.getElementById("DISCOPOGO")) {
      var DISCOPOGO = document.createElement("div");
      DISCOPOGO.id = "DISCOPOGO";
      DISCOPOGO.innerHTML = 
          "<video autoplay loop><source src='discopogo.mp4#t=14' type='video/mp4'></video>";
      errors.appendChild(DISCOPOGO);
    }
    showSpinnies(false);
  }
  
  //Formats and gets meaning data
  function findMeaning() {
    var name = document.getElementById("allnames").value;
    var query = "?type=meaning&name=" + name;
    ajaxify(query, interpretMeaning);
  }
  
  //Handles the returned meaning data from the server
  function interpretMeaning() {
    if (this.status == 200) {
      var meaningDiv = document.getElementById("meaning");
      meaningDiv.innerHTML = this.responseText;
      stripLoader("originmeaning");
    } else {
      fail(this.status);
    }
  }
  
  //Formats and gets rank data
  function findRank() {
    var name = document.getElementById("allnames").value;
    var gender = "m";
    if (document.getElementById("genderf").checked) {
      gender = "f";
    }
    var query = "?type=rank&name=" + name + "&gender=" + gender;
    ajaxify(query, interpretRank);
  }
  
  //Handles the returned rank data from the server
  function interpretRank() {
    if (this.status == 200) {
      //bind and create elements
      var table = document.getElementById("graph");
      var headers = document.createElement("tr");
      var divs = document.createElement("tr");
      var ranks = this.responseXML.getElementsByTagName("rank");
      divs.classList.add("graphHeight");
      //for each piece of data, set the year header
      //and create the data div with the correct height
      for (var i = 0; i < ranks.length; i++) {
        var head = document.createElement("td");
        head.innerHTML = ranks[i].getAttribute("year");
        headers.appendChild(head);
        var rank = document.createElement("td");
        var rankDiv = document.createElement("div");
        rankDiv.innerHTML = ranks[i].textContent;
        rankDiv.classList.add("rank");
        var height = Math.floor(((1000 - parseInt(ranks[i].textContent)) / 4));
        //handle case if there was no data
        if (parseInt(ranks[i].textContent) == 0) {
          height = 0;
        }
        rankDiv.style.height = height + "px";
        //then append the data into the correct table row   
        rank.appendChild(rankDiv);
        divs.appendChild(rank);
      }
      //then append the freshly made table rows into the table
      table.appendChild(headers);
      table.appendChild(divs);
    } else if (this.status == 410) {
      document.getElementById("norankdata").style.display = "";
    } else {
      fail(this.status);
    }
    stripLoader("grapharea");
  }
  
  //Formats and gets celeb data
  function findCelebs() {
    var name = document.getElementById("allnames").value;
    var gender = "m";
    if (document.getElementById("genderf").checked) {
      gender = "f";
    }
    var query = "?type=celebs&name=" + name + "&gender=" + gender;
    ajaxify(query, interpretCelebs);
  }
  
  //Handles the returned celebrity data from the server
  function interpretCelebs() {
    if (this.status == 200) {
      var res = JSON.parse(this.responseText);
      var actorList = document.getElementById("celebs");
      for (var i = 0; i < res["actors"].length; i++) {
        var cur = res["actors"][i];
        var li = document.createElement("li");
        var filmString = "films";
        if (cur["filmCount"] == 1) {
          filmString = "film"; //CRAFTSMANSHIP!
        }
        li.innerHTML = cur["firstName"] + " " + cur["lastName"] +
            " (" + cur["filmCount"] + " " + filmString + ")";
        actorList.appendChild(li);
      } 
    } else {
      fail(this.status);
    }
    stripLoader("celebsarea");
  }
  
  //======== MetaFunctions (so meta) =========
  
  //Requires an id (18+) to strip the loader from the div with the passed id
  function stripLoader(id) {
    var spinny = document.querySelector("#" + id + " .loading");
    spinny.style.display = "none";
  }
  
  //meta-ajax request taking in the necessary query string
  //and the function name to call
  function ajaxify(query, functionName) {
    var ajax = new XMLHttpRequest();
    ajax.onload = functionName;
    ajax.open("GET", BABY_API_URL + query, true);
    ajax.send();
  }
  
  //shows all the loading divs again
  function showSpinnies(isWanted) {
    var spinnies = document.querySelectorAll("#resultsarea .loading");
    for (var i = 0; i < spinnies.length; i++) {
      if (isWanted) {
        spinnies[i].style.display = "";
      } else {
        spinnies[i].style.display = "none";
      }
      
    }
  }
  
})();