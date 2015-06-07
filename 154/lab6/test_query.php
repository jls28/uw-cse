<!DOCTYPE html>
<html>
	<!-- This is a test page that you can use to make sure you're able to
	     perform queries in MySQL properly on the server. -->
	
	<head>
		<title>CSE 154 Database Query Test</title>
	</head>

	<body>

		<?php
		# connect to the imdb_small database
		$db = new PDO("mysql:dbname=imdb_small", "sdierauf", "f7atsJHNDB");
		$db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

		# query the database to see the movie names
		/*
$rows = $db->query("SELECT role
							FROM roles
							JOIN movies ON movies.id = roles.movie_id
							WHERE movies.name = 'Pi';");
*/
		$rows = $db->query("SELECT actors.first_name, actors.last_name, role
							FROM roles
							JOIN movies ON movies.id = roles.movie_id
							JOIN actors ON actors.id = roles.actor_id
							WHERE movies.name = 'Pi';");
							
							/* exercise 7
SELECT DISTINCT first_name, last_name, m1.name, m2.name
							FROM actors
							JOIN roles r1 ON r1.actor_id = actors.id
							JOIN movies m1 ON m1.id = r1.movie_id
							JOIN roles r2 ON r2.actor_id = actors.id
							JOIN movies m2 ON m2.id = r2.movie_id
							WHERE m1.name = 'Kill Bill: Vol. 1' 
							AND m2.name = 'Kill Bill: Vol. 2';
*/
		foreach ($rows as $row) {
			?>

			<p> <?= $row["name"] ?> </p>

			<?php
		}
		?>

	</body>
</html>
