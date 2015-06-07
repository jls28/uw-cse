<?php
	//Stefan Dierauf May 2014
	//the initial web page describing the site with a form for the user to log in or register
	include "common.php";

?>
	<div id="main">
		<?php
			if(isset($_GET["fail"])) {
		?>
			<div id="error"><?=errorhandler($_GET["fail"])?></div>
		<?php	
		}
		?>
		<p>
			The best way to manage your tasks. <br />
			Never forget the cow (or anything else) again!
		</p>

		<p>
			Log in now to manage your to-do list. <br />
			If you do not have an account, one will be created for you.
		</p>

		<form id="loginform" action="login.php" method="post">
			<div><input name="name" type="text" size="8" autofocus="autofocus" /> <strong>User Name</strong></div>
			<div><input name="password" type="password" size="8" /> <strong>Password</strong></div>
			<div><input type="submit" value="Log in" /></div>
		</form>

		<p>
			<em>(last login from this computer was <?=getLastLogin() ?>)</em>
		</p>
	</div>

<?php bottom();
	//returns the correct error string for the given error code
	function errorhandler($error) {
		if ($error == "badpassword") {
			return "You entered the wrong password. Please try again.";
		} else if ($error == "invalidpassword") {
			return "That password does not fit the required pattern.";
		} else if ($error == "invalidname") {
			return "That username does not fit the required pattern.";
		} else {
			return "Oops! Looks like you forgot to enter something.";
		}
	}
?>
