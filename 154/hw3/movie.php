<!DOCTYPE html>
<!--
Stefan Dierauf CSE April 2014 Section BG
Rotten Tomatos featuring TMNT movie review <del>html</del> PHP!
All extra features implemented.
-->

<html>

	<?php //Set up page variables
	
		$movie = "tmnt";
		if (isset($_GET["film"])) {
			if (movieexists($_GET["film"])) {
				$movie = $_GET["film"];
			} else {
				throwerror("Error: film not found.");
			}
		} else {
			throwerror("Error: no film specified");
		}
			
		list($movietitle, $movieyear, $movierating) = file($movie . "/info.txt", FILE_IGNORE_NEW_LINES);
		$overviewimg = $movie . "/overview.png";
		$overviewdata = file($movie . "/overview.txt", FILE_IGNORE_NEW_LINES);
		
		$numreviewswanted = 10;
		if (isset($_GET["reviews"])) {
			$numreviewswanted = $_GET["reviews"];
		}
		
		$reviewfiles = glob($movie . "/review*.txt");
		$numtotalreviews = count($reviewfiles);
		
		if ($numtotalreviews > $numreviewswanted) {
			$reviewfiles = array_slice($reviewfiles, 0, $numreviewswanted);
		} else {
			$numreviewswanted = $numtotalreviews;
		}
	?>

	<head>
		<title>Rancid Tomatoes <?="- $movietitle"?></title>

		<meta charset="utf-8" />
		<link href="movie.css" type="text/css" rel="stylesheet" />
		<link href="https://webster.cs.washington.edu/images/rotten.gif" rel="icon" type="image/x-icon" />
	</head>

	<body>
	
		<!-- Header -->
		
		<?php printheader("headertop"); ?>

		<h1><?=$movietitle . " (" . $movieyear . ")" ?></h1>
		
		<!-- end Header -->
		
		
		<!-- Content -->
		
		<div id='content'>
		
			<!-- Sidebar -->
		
			<div id="sidebar">
				<div>
					<img src=<?=trim($overviewimg) ?> alt="general overview" />
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
			
				<?php printratingheader($movierating, $numtotalreviews)?>
				
				<?php reviews($reviewfiles, $numreviewswanted); ?>
				
			</div>
			
			<!-- end Reviews -->
			
			<!-- Footer -->
			
			<div id="footer">
				<p>(1-<?= min($numreviewswanted, $numtotalreviews) ?>) of <?=$numtotalreviews ?></p>

				<div>
					<a href="https://webster.cs.washington.edu/validate-html.php"><img src="https://webster.cs.washington.edu/images/w3c-html.png" alt="Valid HTML5" /></a><br />
					<a href="https://webster.cs.washington.edu/validate-css.php"><img src="https://webster.cs.washington.edu/images/w3c-css.png" alt="Valid CSS" /></a>
				</div>
			</div>
			
			<!-- end Footer -->
			
			<?php printratingheader($movierating, $numtotalreviews) ?>
			
		</div>

		<!-- end Content -->
		
		<?php printheader("headerbottom"); ?>
		
	</body>
</html>

	



<?php
	//lets write some FUNctions!

	//prints a div with the passed $class variable as its class
	//intended for printing the header at the top and bottom of the page
	//...I know it's gross...
	function printheader($class) {
	?>
		<div class="<?=$class ?>">
			<img src="https://webster.cs.washington.edu/images/rancidbanner.png" alt="Rancid Tomatoes" />
		</div>
	<?php	
	}
	
	//prints the rating header with either fresh.gif or rotten.gif based on the number of positive ratings
	//rating and numreviews should both be integers
	function printratingheader($rating, $numreviews) {
	?>
		<div class="ratingheader">
			<img src="https://webster.cs.washington.edu/images/<?=trim(whichimg($rating))?>" alt="Rotten" /><span class="whitespace">
			</span><?=$rating ?><span class="small">% (out of <?=$numreviews ?> reviews)</span>
		</div>
	<?php	
	}	
	
	//returns true if moviename exists as a folder in the current directory
	//moviename should be a string
	function movieexists($moviename) {
		foreach (scandir(".") as $filename) {
			if (!($filename == "." || $filename == ".." || is_file($filename))) {
				if ($filename == $moviename) {
					return true;
				}
			}
		}
		return false;
	}
	
	//prints a GIANT error message with the passed text
	function throwerror($text) {
	?>
		<h1 class="bigerror"><?=$text?></h1>
	<?php
	}

	//returns the name of which image file should be used (for the ratingheader) based on $rating
	//rating should be an integer 
	function whichimg($rating) {
		if ($rating > 60) {
			return "freshlarge.png";
		} else {
			return "rottenlarge.png";
		}
	}

	//function for determining the number of reviews for each column of reviews in the body
	//$reviewsarray is an array of the review*.txt files
	//$numreviews is the number of reviews, either requested or maximum, whichever is less
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
	
	//builds a column of reviews containing each review in $reviewsarray
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
					<img src="https://webster.cs.washington.edu/images/<?=trim($rotten)?>.gif" alt="<?=trim($rotten)?>.gif"/>
					<q><?=trim($review)?></q>
				</p>
				<p>
					<img src="https://webster.cs.washington.edu/images/critic.gif" alt="Critic" />
					<?=$reviewersname . "<br />\n <span>" . $reviewerscorp . "</span>" ?>
				</p>
			</div>
		<?php } ?>
		</div>
	<?php } 
?>
