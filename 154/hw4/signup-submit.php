<?php
	//Stefan Dierauf April 2014 CSE 154
	//submit page for signing up a new user
	//Majors only features 2 and 3 completely added (sexualities and user photos)
	
  include 'common.php';
	
	$name = getname();
	$gender = getfield("gender", "/(M|F)/");
	$age = getfield("age", "/[0-9]{1,2}/");
	$ptype = getfield("ptype", "/(I|E)(N|S)(F|T)(J|P)/");
	$favos = getfield("favos", "/(Windows|Linux|OS X)/");
	$minage = getfield("minage", "/[0-9]{1,2}/");
	$maxage = getfield("maxage", "/[0-9]{1,2}/");
	$wannabang = getwannabang();

	$dataPack = array($name, $gender, $age, $ptype, $favos, $minage, $maxage, $wannabang);
	
	addLine("singles2.txt", $dataPack);
	handlePhoto($name);
?>
		
		<div>
			<p><strong>Thank you!</strong></p>
			<p>Welcome to NerdLuv, <?=$name ?></p>
			<p>Now <a href="matches.php">log in to see your matches!</a></p>
		</div>
		
<?php bottom();
	
	//Gets a certain post field and checks it against a given regular expression
	//implemented as part of part 1 of the majors only section but was never finished
	function getfield($post, $regex) {
		if (isset($_POST[$post]) && preg_match($regex, $_POST[$post]) == true) {
			return $_POST[$post];
		}
	}
	
	//Gets the desired opposite gender from POST
	function getwannabang() {
		if (isset($_POST["seekingm"]) || isset($_POST["seekingf"])) {
			$ret = "";
			if (isset($_POST["seekingm"])) {
				$ret = $ret . "M";
			}
			if (isset($_POST["seekingf"])) {
				$ret = $ret . "F";
			}
			return $ret;
		}
	}

	//gets the name from POST
	function getname() {
		if (isset($_POST["name"]) && strpos(file_get_contents("singles2.txt"), $_POST["name"]) === false) {
			return $_POST["name"];
		}
	}
	
	//Adds a line containing the new user's information to the given file
	function addLine($filename, $stuff) {
	  if(!file_exists($filename)) {
	    file_put_contents($filename, "");
	    chmod($filename, 0777);
	  }
	  $temp = file_get_contents($filename);
	  $string = "\n" . implode(",", $stuff);
	  $temp = $temp . $string;
	  file_put_contents($filename, $temp);
	}
	
	//Adds and renames a new user's photo to the images/ directory.
	function handlePhoto($thename) {
	  $thename = explode(" ", $thename);
	  $thename = implode("_", $thename);
	  $thename = strtolower($thename);
		if(is_uploaded_file($_FILES["file"]["tmp_name"])) {
		  chmod($_FILES["file"]["tmp_name"], 0777);
			rename($_FILES["file"]["tmp_name"], "images/" . $thename . ".jpg");
		}
	}
	
	
?>