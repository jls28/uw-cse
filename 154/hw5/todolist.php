<?php
	//Stefan Dierauf May 2014
	//Main todolist.php for remember the cow
	//All CS Majors only features implemented
	
	include "common.php";
	
	session_start();
	
	$mydata = array();
	
	//get the user's data, otherwise make a new file for the user to put data
	if (file_exists("todo_" . $_SESSION["name"] . ".txt")) {
		$mydata = file("todo_" . $_SESSION["name"] . ".txt");
	} else {
		file_put_contents("todo_" . $_SESSION["name"] . ".txt", "");
	}
	chmod("todo_" . $_SESSION["name"] . ".txt", 0777);
	
?>

		<div id="main">
			<h2><?=$_SESSION["name"] ?>'s To-Do List</h2>
			<?php
			  if (isset($_GET["fail"])) {
	  			  if ($_GET["fail"] == "invalid") {
	  			    $string = "You tried to add only whitespace!";
	  			  } elseif ($_GET["fail"] == "outofbounds") {
	    			  $string = "You tried to delete something that was out of bounds!";
	  			  }
  			  ?>
    			    <div id="error"> <?=$string ?></div>
          <?php
			  }
			?>

			<ul id="todolist">
			
				<?php printlist($mydata) ?>
				
				<li>
					<form action="submit.php" method="post">
						<input type="hidden" name="action" value="add" />
						<input name="item" type="text" size="25" autofocus="autofocus" />
						<input type="submit" value="Add" />
					</form>
				</li>
			</ul>

			<div>
				<a href="logout.php"><strong>Log Out</strong></a>
				<em>(logged in since <?=getlastlogin()?>)</em>
			</div>

		</div>

<?php bottom();

	//prints a list of given data with an index
	function printlist($data) {
		$count = 0;
		foreach($data as $datum) {
			printitem($datum, $count);
			$count += 1;
		}
	}
	
	//prints a single line item of a list
	function printitem($data, $index) {
	?>
		<li>
			<form action="submit.php" method="post">
				<input type="hidden" name="action" value="delete" />
				<input type="hidden" name="index" value=<?=$index ?> />
				<input type="submit" value="delete" />
			</form>
			<?=$data ?>
		</li>
	<?php
	}
?>

	