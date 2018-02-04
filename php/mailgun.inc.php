<?php
	$from = "Your Name <you@somewhere>";
	$to = "Your Self <you@somewhere-else>";
	$domain = "your-domain";
	$api_key = "your-mailgun-api-key";

function mailgun_send($api_key, $domain, $from, $to, $subject, $body)
{
	$fields = array(
		"from" => $from,
		"to" => $to,
		"subject" => $subject,
		"html" => $body
	);

	$curl = curl_init();
	curl_setopt($curl, CURLOPT_URL, "https://api.mailgun.net/v3/" . $domain . "/messages");
	curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
	curl_setopt($curl, CURLOPT_FOLLOWLOCATION, true);
	curl_setopt($curl, CURLOPT_USERPWD, "api:" . $api_key);
	curl_setopt($curl, CURLOPT_POST, count($fields));
	curl_setopt($curl, CURLOPT_POSTFIELDS, $fields);
	$result = curl_exec($curl);
	curl_close($curl);
	return $result;
}

?>
