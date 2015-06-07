<?php
  //Stefan Dierauf May 2014
  //Search all for one degree of kevin bacon
  //extra feature of special info about the actor included
  
	include 'common.php';
	$title = "Results for " . $firstname . " " . $lastname;	
	$rows = getrows(false, $db, $person);
	top($title);
	
  if (count($person) > 1) {
    $numberthe = 0;
    $numbernotthe = 0;
	  tabletop($firstname, $lastname);
		$i = 0;
		$min = 99999999; //will stop workign after this year :)
		$max = 0;
		$avg = 0;
		$lastyear = 0;
		foreach($rows as $row) {
		  $i++;
		  if ($row["year"] < $min) {
			  $min = $row["year"];
		  }
		  if ($row["year"] > $max) {
			  $max = $row["year"];
		  } 
		  if ($lastyear == 0) {
			  $lastyear = $row["year"];
		  } else {
			  $avg = $avg + ($lastyear - $row["year"]);
			  $lastyear = $row["year"];
		  }
		  if (preg_match("/the/i", $row["name"])) {
			  $numberthe++;
		  } else {
			  $numbernotthe++;
		  }
      eachrow($i, $row["name"], $row["year"]);
		}
		$avgnumyears = $avg / $i;
		$numyears = $max - $min;
		?>
		
		</tbody>
	</table>
	<dl>
	  <dt>Number of years working in film:</dt>
	  <dd><?=$numyears ?>
	  
	  <dt>Average number of years between each film</dt>
	  <dd><?=$avgnumyears ?></dd>
	  
	  <dt>Number of movies with 'the' in the title</dt>
	  <dd><?=$numberthe ?></dd>
	  
	  <dt>Number of movies withOUT 'the' in the title</dt>
	  <dd><?=$numbernotthe ?></dd>
	  
	  <dt>Gender</dt>
	  <dd><?=$person["gender"] ?></dd>
	  
	</dl>
	
<?php
  } else {
    errorblock($firstname, $lastname, "not found");
  }
  searchform();
  bottom();
?>