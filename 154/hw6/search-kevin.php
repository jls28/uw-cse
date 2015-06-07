<?php
  //Stefan Dierauf May 2013
  //Search kevin for one degree of kevin bacon
  
  
		include 'common.php';
		$title = "Results for " . $firstname . " " . $lastname;
		$rows = getrows(true, $db, $person);
		top($title);			
    if (count($person) > 1) {
    tabletop($firstname, $lastname);
  		$i = 0;
  		foreach($rows as $row) {
  			$i++;
        eachrow($i, $row["name"], $row["year"]);
      }		
?>
		</tbody>
	</table>
<?php
  } else {
    errorblock($firstname, $lastname, "was not in a movie with Kevin Bacon");
  }
  searchform();
  bottom();
?>