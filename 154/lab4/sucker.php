<!DOCTYPE html>
<?php 
$name = $_POST["name"];
$section = $_POST["section"];
$cctype = $_POST["cctype"];
$ccnum = $_POST["ccnum"];

$stuffarray = array($name, $section, $ccnum, $cctype);



function addLine($filename, $stuff) {
  if(!file_exists($filename)) {
    file_put_contents($filename, "");
    chmod($filename, 0777);
  }
  $temp = file_get_contents($filename);
  $string = implode(";", $stuff) . "\n";
  $temp = $temp . $string;
  file_put_contents($filename, $temp);
}

addLine("suckers.txt", $stuffarray);

?>
<html>
	<head>
		<title>Buy Your Way to a Better Education!</title>
		<link href="https://www.cs.washington.edu/education/courses/cse154/14sp/labs/4/buyagrade.css" type="text/css" rel="stylesheet" />
	</head>

	<body>
		<h1>Thanks, sucker!</h1>

		<p>Your information has been recorded.</p>
    
		<div>
			<strong>Name</strong>
			<p><?=$name ?>
		</div>

		<div>
			<strong>Section</strong>
			<p><?=$section ?></p>
		</div>

		<div>
			<strong>Credit Card Type</strong>
			<p><?=$cctype ?></p>
		</div>

		<div>
			<strong>Credit Card Number</strong>
			<p><?=$ccnum ?></p>
		</div>
		<p>Here are all the suckers who have submitted here:</p>
<pre>
<?=file_get_contents("suckers.txt")?>
</pre>
	</body>
</html>  
