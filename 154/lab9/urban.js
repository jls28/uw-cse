/*
urban dictionary lab
*/


(function() {

  window.onload = function() {
    var lookup = document.getElementById("lookup");
    lookup.onclick = getFromUrbanDictionary;
  }
  
  function getFromUrbanDictionary() {
    var searchTerm = document.getElementById("term").value;
    var ajax = new XMLHttpRequest();
    ajax.onload = doStuff;
    ajax.open("GET", "https://webster.cs.washington.edu/cse154/labs/9/urban.php?term=" + searchTerm + "&all=true", true);
    ajax.send();
  }
  
  function doStuff() {
    var ol = document.createElement("ol");
    var res = this.responseXML;
    var results = res.querySelectorAll("entry");
    for (var i = 0; i < results.length; i++) {
      var li = document.createElement("li");
      var def = document.createElement("p");
      def.innerHTML = results[i].querySelector("definition").textContent;
      var ex = document.createElement("p");
      ex.classList.add("example");
      ex.innerHTML = results[i].querySelector("example").textContent;
      var auth = document.createElement("p");
      auth.classList.add("author");
      auth.innerHTML = "- " + results[i].getAttribute("author");
      auth.onclick = downTheRabbitHole;
      li.appendChild(def);
      li.appendChild(ex);
      li.appendChild(auth);
      ol.appendChild(li);
      //console.log(li);
    }
    document.getElementById("result").appendChild(ol);
  }
  
  function downTheRabbitHole() {
    var searchTerm = this.innerHTML.substring(2);
    var ajax = new XMLHttpRequest();
    ajax.onload = showAuthor;
    ajax.open("GET", "https://webster.cs.washington.edu/cse154/labs/9/urban.php?author=" + searchTerm, true);
    console.log("https://webster.cs.washington.edu/cse154/labs/9/urban.php?author=" + searchTerm);
    ajax.send();
  }
  
  function showAuthor() {
    var res = this.responseXML;
    var h2 = document.createElement("h2");
    h2.innerHTML = res.firstChild.firstChild.getAttribute("author");
    var p = document.createElement("p");
    var words = res.getElementsByTagName("word");
    for (var i = 0; i < words.length - 1; i++) {
      var word = document.createElement("span");
      word.innerHTML = words[i].getAttribute("entry");
      word.onclick = function() {
        document.getElementById("term").value = this.innerHTML;
      }
      p.appendChild(word);
      p.innerHTML += ", ";
      
    }
    var word = document.createElement("span");
    word.innerHTML = words[words.length - 1].getAttribute("entry");
    word.onclick = function() {
      document.getElementById("term").value = this.innerHTML;
    }
    var related = document.getElementById("related");
    related.appendChild(h2);
    related.appendChild(p);
  }

  



  
})();


/*

var ajax = new XMLHttpRequest();
ajax.onload = functionName;
ajax.open("GET", "url", true);
ajax.send();
...
function functionName() {
  do something with this.responseText;
}

*/
