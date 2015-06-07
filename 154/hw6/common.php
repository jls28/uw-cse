<?php
  //Stefan Dierauf May 2014
  //Common php code for One degree of Kevin Bacon
  //Extra feature: more info about the actor

	$firstname = safeget("firstname");
	$lastname = safeget("lastname");
	
	//set up the database object
	$db = new PDO("mysql:dbname=imdb;host=localhost", "sdierauf", "f7atsJHNDB");
	$db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
	
	//get the person's ID and Gender (For extra features :D )
	$person = $db->query("SELECT id, gender FROM actors
								WHERE actors.last_name = " . $db->quote($lastname) . "
								AND actors.first_name LIKE " . $db->quote($firstname . "%") . "
								ORDER BY film_count DESC, id ASC
								LIMIT 1;")->fetch();
	
	
	//Safely returns the passed field	
	function safeget($field) {
		if (isset($_GET[$field])) {
			return ucfirst($_GET[$field]);
		}
	}

  //Prints the top of the page
  function top($title) {
    ?>
    <!DOCTYPE html>
    <html>
    <head>
      <title><?=$title ?></title>
    	<link href="bacon.css" type="text/css" rel="stylesheet" >
    	<meta charset="utf-8" />
      <link href="https://webster.cs.washington.edu/images/kevinbacon/favicon.png" type="image/png" rel="shortcut icon" />
    </head>
    
    <body>
    	<div id="content">
    		<div class="header">
    			<img src="https://webster.cs.washington.edu/images/kevinbacon/mymdb.png" alt="mymdb pic" />
    			<span>My Movie Database</span>
    		</div>
    
    <?php
  }

  //builds the correct query and then returns the database results of the query
  function getrows($kevin, $database, $person) {
    $q = "SELECT name, year FROM movies
  						JOIN roles ON roles.movie_id = movies.id
  						JOIN actors ON actors.id = roles.actor_id";
  						
  						
    if ($kevin) {
      $q = $q . "\nJOIN roles r2 ON r2.movie_id = movies.id
              JOIN actors a2 ON a2.id = r2.actor_id
  						WHERE actors.id = " . $person["id"] . 
  						"\nAND a2.last_name = 'Bacon'
              AND a2.first_name = 'Kevin'";
    } else {
      $q = $q . "\nWHERE actors.id = " . $person["id"];
    }
    $q = $q . "\nORDER BY year DESC, name ASC;";
    
    return $database->query($q);
    
  }

  //prints an error block with a lame picture
  function errorblock($firstname, $lastname, $string) {
  ?>
    <div id="error">
      <p>Actor <?=$firstname . " " . $lastname . " " . $string ?></p>
      <img src="error.jpg" alt="why" />
    </div>
  <?php 
  }
  
  //Prints the top part of the table
  function tabletop($firstname, $lastname) {
  ?>
  	<h1>Results for '<?=$firstname ?> <?=$lastname ?>'</h1>
  	
  	<table>
  		<thead>
  			<tr>
  				<th>#</th>
  				<th>Name</th>
  				<th>Year</th>
  			</tr>
  		</thead>
  		<tbody>
  <?php  
  }
  
  //Prints each row of the table
  function eachrow($i, $name, $year) {
  ?>
    <tr>
  		<td><?=$i ?></td>
  		<td><?=$name ?></td>
  		<td><?=$year ?></td>
    </tr>
  <?php
  }
  
  //Prints the search form for each page
  function searchform() {
  ?>
    <form action="search-all.php" method="get">
  		<fieldset>
  			<legend>All movies</legend>
  			<div>
  				<input name="firstname" type="text" size="12" placeholder="first name" autofocus="autofocus" /> 
  				<input name="lastname" type="text" size="12" placeholder="last name" /> 
  				<input type="submit" value="go" />
  			</div>
  		</fieldset>
  	</form>
  
  	<!-- form to search for movies where a given actor was with Kevin Bacon -->
  	<form action="search-kevin.php" method="get">
  		<fieldset>
  			<legend>Movies with Kevin Bacon</legend>
  			<div>
  				<input name="firstname" type="text" size="12" placeholder="first name" /> 
  				<input name="lastname" type="text" size="12" placeholder="last name" /> 
  				<input type="submit" value="go" />
  			</div>
  		</fieldset>
  	</form>
  
  <?php
  }
  
  //Prints the bottom of each page
  function bottom() {
    ?>
    <div class="header"> 
  			<a href="https://webster.cs.washington.edu/validate-html.php"><img src="https://webster.cs.washington.edu/images/w3c-html.png" alt="Valid HTML5" /></a>
  					<a href="https://webster.cs.washington.edu/validate-css.php"><img src="https://webster.cs.washington.edu/images/w3c-css.png" alt="Valid CSS" /></a>
  		</div>
  		
  	</div>
  
  </body>
  </html>
    <?php
  }

?>