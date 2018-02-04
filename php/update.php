<!DOCTYPE html>
<html dir="ltr" lang="en">
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
	<meta name="viewport" content="width=device-width">
	<title>Updating website</title>
	<link rel="shortcut icon" href="/favicon.ico" type="image/x-icon" />
	<link rel="icon" href="/favicon.ico" type="image/x-icon" />
	<style>
html {
	height: 100%;
}

body {
	font-size: 16px;
	font-family: tahoma, geneva, sans-serif;
	height: 100%;
	color: black;
}
	</style>
</head>
<body>
<?php
	chdir("/var/www/schau.dk/public_html");
	$output = array();
	$return_code = 0;
	exec("/usr/bin/git pull origin master", $output, $return_code);
	echo "<p><pre>";
	foreach ($output as $line) {
		echo $line . "<br />";
	}
	echo "</pre></p>";
	echo "<p>Return code: " . $return_code . "</p>";
?>
</body>
</html>
