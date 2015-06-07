<?php
	//Stefan Dierauf CSE 154 May 2014
	//matches.php for NerdLuv
	//Prompts user for name to get matches based on their data.

	include 'common.php';
?>	
	<form action="matches-submit.php" method="post">
		<fieldset>
			<legend>Returning User:</legend>
			<div>
				<label><strong>Name: </strong></label>
				<input type="text" name="name" size="16" />
			</div>
			<div>
				<input type="submit" value="View My Matches" />
			</div>
		</fieldset>
	</form>
		
<?php bottom() ?>