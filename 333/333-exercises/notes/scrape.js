l = document.querySelectorAll("a");
s = [];
for (var i = 0; i < l.length; i++) {
    s.push(l[i].getAttribute("href") + "");
}
txt = s.filter(function(e) { return e.indexOf(".txt") >= 0 }).map(function(e) { return "http://courses.cs.washington.edu/courses/cse333/15wi/" + e });
console.log(txt);
