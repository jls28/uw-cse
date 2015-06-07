
<?php
	//Stefan Dierauf CSE 154 May 2014
	//matches-submit.php for NerdLuv
	//extra CSE majors features 2 and 3 implemented
  include 'common.php';
  
	$myname = getname();
	$mymatches = getmatches($myname);
	
?>
		<p><strong>Matches for <?=$myname ?></strong></p>
			
<?php printMatches($mymatches); 
	bottom();
	
	//Gets the name from the POST request
	function getname() {
		if (isset($_POST["name"])) {
			return $_POST["name"];
		}
	}
	
	//returns array of matches data for a given name string
	function getmatches($name) {
		$matches = array();
		$mydata = "";
		$data = file("singles2.txt");
		foreach($data as $line) {
			if(strpos($line, $name) === 0) {
				//print $line;
				$mydata = $line;
			}
		}
		if (count_chars($mydata) == 0) {
			exit("You don't exist!");
		}
		
		list($myname, $mygender, $myage, $mytype, $myos, $minage, $maxage, $wannabang) = explode(",", $mydata);
		
		foreach($data as $line) {
			list($theirname, $theirgender, $theirage, $theirtype, $theiros, $theirmin, $theirmax, $theirwannabang) = explode(",", $line);
			$theirwannabang = trim($theirwannabang);
			$typematch = false;
			for ($i = 0; $i < 4; $i++) {
				if ($theirtype{$i} == $mytype{$i}  && strpos($theirwannabang, $mygender) !== false  
				&& strpos($wannabang, $theirgender) !== false) {
					$typematch = true;
				}	
			}
				if ($theirname != $myname && $theirage <= $maxage && $theirage >= $minage 
				&& $myage <= $theirmax && $myage >= $theirmin && $theiros == $myos && $typematch) {
				array_push($matches, $line);
			}
		}
		return $matches;
	}
	
	//prints the data of the given array of matches
	function printMatches($matches) {
		foreach($matches as $match) {
		list($name, $gender, $age, $type, $os) = explode(",", $match);
		$imgname = implode("_", explode(" ",  strtolower($name)));
		$imgpath = "";
		if (strpos(implode(" ", scandir("images/")), $imgname) !== false) {
			$imgpath = "images/" . $imgname;
		} else {
			$imgpath = "https://webster.cs.washington.edu/images/nerdluv/" . $imgname;
		}
		?>
		
  		<div class="match">
  			<p><img src="<?=$imgpath ?>.jpg" alt="user pic" /> <?=$name ?></p>
  			<ul>
  				<li><strong>gender: </strong> <?=$gender ?></li>
  				<li><strong>age: </strong> <?=$age ?></li>
  				<li><strong>type: </strong> <?=$type ?></li>
  				<li><strong>OS: </strong> <?=$os ?></li>
  			</ul>
  		</div>
		
		<?php
		}
	}
	
?>
		
		