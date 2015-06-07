<?php
  //Stefan Dierauf May 2014
  //Main landing page for one degree of kevin bacon 
  $title = "MyMDb";
  include 'common.php';
  top($title);
?>


			<div id="main">
				<h1>The One Degree of Kevin Bacon</h1>
				<p>Type in an actor's name to see if he/she was ever in a movie with Kevin Bacon!</p>
				<p><img src="https://webster.cs.washington.edu/images/kevinbacon/kevin_bacon.jpg" alt="Kevin Bacon" /></p>

				<!-- form to search for every movie by a given actor -->
				<?php searchform() ?>
			</div> <!-- end of #main div -->

<?php bottom(); ?>