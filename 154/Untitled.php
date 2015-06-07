<?php
	print "HAIL HYDRA <br>";
	
	function println($string) {
		print $string . "<br>";
	}
	
	println("HAIIIL HYDRA");
	println("fasdfasdfasdfasdf");
	
	function print_separator($str, $separator = ", ") {
		if (strlen($str) == 0) {
			return "";
		} else {
			print $str[0];
			for ($i = 1 ; $i < strlen($str); $i++) {
				print $separator . $str[$i];
			}
		}
	}
	
	print_separator("poop", "-aaaa-a- ");
	
?>

