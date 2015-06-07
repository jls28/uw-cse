<?php
	//Stefan Dierauf May 2014
	//logout for remember the cow
	//logs out the user and redirects to start.php
	//clear session id so not reused!
	
	session_destroy();
	session_regenerate_id(TRUE);
	
	header("Location: start.php");
?>