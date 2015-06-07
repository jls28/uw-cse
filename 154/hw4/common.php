<?php
//Stefan Dierauf April 2014 CSE 154
//php file of common functions for Nerdluv

//Prints the top chunk of html common to every page
function top() {
?>
<!DOCTYPE html>
<html>
	<head>
		<title>NerdLuv</title>
		
		<meta charset="utf-8" />
		<meta name="keywords" content="nerd, luv, dating, match, date, online" />
		<meta name="description" content="a site for single nerds to meet each other" />
		
		<!-- instructor-provided CSS and JavaScript links; do not modify -->
		<link href="https://webster.cs.washington.edu/images/nerdluv/heart.gif" type="image/gif" rel="shortcut icon" />
		<link href="https://webster.cs.washington.edu/css/nerdluv.css" type="text/css" rel="stylesheet" />
	</head>

	<body>
		<div id="bannerarea">
			<img src="https://webster.cs.washington.edu/images/nerdluv/nerdluv.png" alt="banner logo" /> <br />
			where meek geeks meet
		</div>

<?php
}


//prints the bottom chunk of html common to every page
//including w3c validator links
function bottom() {
?>
    <div>
  			<p>
  				This page is for single nerds to meet and date each other!  Type in your personal information and wait for the nerdly luv to begin!  Thank you for using our site.
  			</p>
  			
  			<p>
  				Results and page (C) Copyright NerdLuv Inc.
  			</p>
  			
  			<ul>
  				<li>
  					<a href="nerdluv.php">
  						<img src="https://webster.cs.washington.edu/images/nerdluv/back.gif" alt="icon" />
  						Back to front page
  					</a>
  				</li>
  			</ul>
  		</div>
  
  		<div id="w3c">
  			<a href="https://webster.cs.washington.edu/validate-html.php"><img src="https://webster.cs.washington.edu/images/w3c-html.png" alt="Valid HTML" /></a>
  			<a href="https://webster.cs.washington.edu/validate-css.php"><img src="https://webster.cs.washington.edu/images/w3c-css.png" alt="Valid CSS" /></a>
  		</div>
  	</body>
  </html>
<?php 
}

top();
?>