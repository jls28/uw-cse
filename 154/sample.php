<?php
	$string = "DESTROY ALL HUMANS";
	for($i = 0; $i < strlen($string); $i++) {
		print "<p> $string[$i] </p>";
		if ($string[$i] == " ") {
			print "<br />";
		}
	}


?>


<?php
	$style = "style=font-size:3em";
	// $newstyle = $style . ", color: red";
	for($i = 1; $i <= 100; $i++) {
		print "<span $style> $i </span>";
		print "<span> $i . 4 </span>";
	}
?>