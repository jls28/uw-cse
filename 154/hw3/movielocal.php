
<!--
Stefan Dierauf CSE April 2014 Section BG
Rotten Tomatos featuring TMNT movie review <del>html</del> PHP!
All extra features implemented.
-->

<?php
	chdir("/Users/sdierauf/Dropbox/cse154/hw3"); //change for web version.
	$movie = "tmnt2"; /* $_GET["film"]; */
	$files = glob($movie . "/*.*");
	$info = "something";
	$overviewimg = "";
	$overviewdata = "";
	foreach ($files as $file) {
		if (basename($file) == "info.txt") {
			$info = file($file, FILE_IGNORE_NEW_LINES);
		}
		if (basename($file) == "overview.png") {
			$overviewimg = $file;
		}
		if (basename($file) == "overview.txt") {
			$overviewdata = file($file, FILE_IGNORE_NEW_LINES);
		}
		print $file;
	}
	$numreviewswanted = 10; /* $_GET["reviews"]; */
	print getcwd();
	$movietitle = $info[0];
	$movieyear = $info[1];
	$movierating = $info[2];
	
	
	
	$reviewfiles = glob($movie . "/review*.txt");
	
	if (count($reviewfiles) > $numreviewswanted) {
		$reviewfiles = array_slice($reviewfiles, 0, $numreviewswanted);
	}	
	
?>

<!-- lets write some FUNctions! TODO move to bottom -->

<?php

	function whichimg($rating) {
		if ($rating > 60) {
			return "freshlarge.png";
		} else {
			return "rottenlarge.png";
		}
	}

	function reviews($reviewsarray, $numreviews) {
		$half = count($reviewsarray) / 2;
		if ($numreviews < 2) {
			reviewscol(array_slice(0, $numreviews));
		} elseif ($numreviews % 2 == 0) {
			reviewscol(array_slice($reviewsarray, 0, $half));
			reviewscol(array_slice($reviewsarray, $half, count($reviewsarray)));
		} elseif ($numreviews % 2 == 1) { //could be just else
			reviewscol(array_slice($reviewsarray, 0, $half + 1));
			reviewscol(array_slice($reviewsarray, $half + 1, count($reviewsarray)));
		}
	}
	
	function reviewscol($reviewsarray) {
	?> 
		<div class= "reviewscol">
	<?php
		foreach($reviewsarray as $review) {
			list($review, $rotten, $reviewersname, $reviewerscorp) = file($review);
			$rotten = strtolower($rotten);
		?>
			<div class="entry">
				<p>
					<img src="https://webster.cs.washington.edu/images/<?=$rotten?>.gif" />
					<q><?=$review ?></q>
				</p>
				<p>
					<img src="https://webster.cs.washington.edu/images/critic.gif" alt="Critic" />
					<?=$reviewersname . "<br \>\n <span>" . $reviewerscorp . "</span>" ?>
				</p>
			</div>
		<?php } ?>
		</div>
	<?php } ?>
	
<!DOCTYPE html>


<html>
	<head>
		<title>Rancid Tomatoes</title>

		<meta charset="utf-8" />
		<link href="movie.css" type="text/css" rel="stylesheet" />
		<link href="https://webster.cs.washington.edu/images/rotten.gif" rel="icon" type="image/x-icon" />
	</head>

	<body>
	
		<!-- Header -->
		
		<!--
<div id="header">
			<img src="https://webster.cs.washington.edu/images/rancidbanner.png" alt="Rancid Tomatoes" />
		</div>
-->
		<h1><?=$movietitle . " (" . $movieyear . ")" ?></h1>
		
		<!-- end Header -->
		
		
		<!-- Content -->
		
		<div id='content'>
		
			<!-- Sidebar -->
		
			<div id="sidebar">
				<div>
					<img src=<?=$overviewimg ?> alt="general overview" />
				</div>

				<dl>
					<?php
						foreach ($overviewdata as $line) {
							list($dt, $dd) = explode(":", $line);
					?>
						<dt><?=$dt?></dt>
						<dd><?=$dd?></dd>
					<?php } ?>
				</dl>
			</div>
			
			<!-- end Sidebar -->
		
		
			<!-- Reviews -->
			<div id="reviews">
				<div id="ratingheader">
					<img src="https://webster.cs.washington.edu/images/<?=whichimg($movierating)?>" alt="Rotten" /><span class="whitespace">
					</span><?=$movierating ?><span class="small">% (out of 88 reviews)</span>
				</div>
				
				<?php reviews($reviewfiles, $numreviewswanted); ?>
				
			</div>
			
			<!-- end Reviews -->
			
			<!-- Footer -->
			
			<div id="footer">
				<p>(1-10) of 88</p>

				<div>
					<a href="https://webster.cs.washington.edu/validate-html.php"><img src="https://webster.cs.washington.edu/images/w3c-html.png" alt="Valid HTML5" /></a><br />
					<a href="https://webster.cs.washington.edu/validate-css.php"><img src="https://webster.cs.washington.edu/images/w3c-css.png" alt="Valid CSS" /></a>
				</div>
			</div>
			
			<!-- end Footer -->
			
		</div>
		
		<!-- end Content -->
		
	</body>
</html>
