<?php
	//Stefan Dierauf April 2014 CSE 154
	//signup form for NerdLuv
	//Majors-only features 2 and 3 implemented

 include 'common.php';
 ?>
		
		<form action="signup-submit.php" method="post" enctype="multipart/form-data">
  		<fieldset>
  		  <legend>New User Signup:</legend>
  		  <div>
  		    <label><strong>Name:</strong></label>
  		    <input type="text" name="name" size="16" />
  		  </div>
  		  <div>
  		    <label><strong>Gender:</strong></label>
  		    <input type="radio" name="gender" value="M" />Male
  		    <input type="radio" name="gender" value="F" />Female
  		  </div>
  		  <div>
  		    <label><strong>Age:</strong></label>
  		    <input type="text" name="age" size="6" maxlength="2"/>
  		  </div>
  		  <div>
  		  <div>
  		    <label><strong>Personality Type:</strong></label>
  	      <input type="text" name="ptype" size="6" maxlength="4" />
  	      <span>(<a href="http://www.humanmetrics.com/cgi-win/JTypes2.asp">Don't know your type?</a>)</span>
  		  </div>
  		    <label><strong>Favorite OS:</strong></label>
  	      <select name="favos">
  	        <option selected>Windows</option>
  	        <option>Mac OS X</option>
  	        <option>Linux</option>
  	      </select>
  		  </div>
  		  <div>
  		    <label><strong>Seeking age:</strong></label>
          <input type="text" name="minage" maxlength="2" size="6" />
          <span> to </span>
          <input type="text" name="maxage" maxlength="2" size="6" />
  		  </div>
  		  <div>
  		  	<label><strong>Seeking Gender(s):</strong></label>
  		  	<input type="checkbox" name="seekingm" value="M" />Male
  		  	<input type="checkbox" name="seekingf" value="F" />Female
  		  </div>
  		  <div>
  		  	<label><strong>Submit a picture:</strong></label>
  		  	<input type="file" name="file" /> 
  		  </div>
  		  <div>
  		    <input type="submit" value="Sign Up" />
  		  </div>
  		</fieldset>	        
		</form>
  
<?php bottom() ?>