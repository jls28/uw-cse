<?php
	$numbersongs = 5678;
	$favartists = array("Britney Spears", "Girl Talk", "Madonna", "P!nk");
?>

<!DOCTYPE html>
<html>
	<!--
	Web Programming Step by Step
	Lab #3, PHP
	-->

	<head>
		<title>Music Viewer</title>
		<meta charset="utf-8" />
		<link href="https://www.cs.washington.edu/education/courses/cse190m/12sp/labs/3/viewer.css" type="text/css" rel="stylesheet" />
	</head>

	<body>
		
		<h1>My Music Page</h1>
		
		<!-- Number of Songs (Variables) -->
		<p>
			I love music.
			I have <?=$numbersongs ?> total songs,
			which is over <?=$numbersongs/10 ?> hours of music!
		</p>

		<!-- Music Results Pages (Loops) -->
		<div class="section">
			<h2>Google's Music Results</h2>
		
			<ol>
				<?php
					$numresults = 10;
					for ($i = 0; $i < $numresults; $i++) {
					?>
					<li><a href="https://www.google.com/search?tbm=nws&amp;q=Music&amp;start=<?=$i*10 ?>">Page <?=$i+1 ?></a></li>
				<?php } ?>
			</ol>
		</div>

		<!-- Favorite Artists (Arrays) -->
		<!-- Favorite Artists from a File (Files) -->
		<div class="section">
			<h2>My Favorite Artists</h2>
		
			<ol>
				<?= favartists($favartists) ?>
			</ol>
		</div>
		
		<!-- Music (Multiple Files) -->
		<!-- MP3 Formatting -->
		<div class="section">
			<h2>My Music and Playlists</h2>

			<ul id="musiclist">
				<li class="mp3item">
					<a href="http://webster.cs.washington.edu/cse154/songs/Be More.mp3">Be More.mp3</a>
				</li>
				
				<li class="mp3item">
					<a href="http://webster.cs.washington.edu/cse154/songs/Just Because.mp3">Just Because.mp3</a>
				</li>

				<li class="mp3item">
					<a href="http://webster.cs.washington.edu/cse154/songs/Drift Away.mp3">Drift Away.mp3</a>
				</li>

				<!-- Exercise 8: Playlists (Files) -->
				<li class="playlistitem">154-mix.m3u:
					<ul>
						<li>Hello.mp3</li>
						<li>Be More.mp3</li>
						<li>Drift Away.mp3</li>
						<li>Panda Sneeze.mp3</li>
					</ul>
				</li>
			</ul>
		</div>

		<div>
			<a href="https://webster.cs.washington.edu/validate-html.php">
				<img src="http://webster.cs.washington.edu/w3c-html.png" alt="Valid HTML5" />
			</a>
			<a href="https://webster.cs.washington.edu/validate-css.php">
				<img src="http://webster.cs.washington.edu/w3c-css.png" alt="Valid CSS" />
			</a>
		</div>
	</body>
</html>

<?php 
	function favartists($artists) {
		foreach($artists as $artist) {
		?>
		<li><?=$artist ?></li>
		<?php
			
		}
	}
?>
