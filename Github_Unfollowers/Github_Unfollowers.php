<?php

/*
This is not an optimized script, but something I just wrote.
The problem with web scraping scripts is inconsistency,
meaning that the content on the web (e.g., HTML data) always changes.
That's why this script may not work in the future.

P.S.: Be careful! "while (true)" statements are risky and might lead to infinite iterations.
*/

if( isset($argv[1]) ) $username = $argv[1];
else die("ERROR: Please enter a username for github." . PHP_EOL);

$followers_url = "https://github.com/$username?tab=followers"; 
$following_url = "https://github.com/$username?tab=following"; 
$dom = new DOMDocument;

// Processing followers:
$followers = [];
$counter = 0;
while (true)
{
    $html = file_get_contents($followers_url . "&page=" . ++$counter);
    if ( strpos($html, "reached the end of") !== false ) break;
    @$dom->loadHTML($html);
    $frame = $dom->getElementsByTagName('turbo-frame');
    $html = "";
    foreach ($frame as $f) {
        $html.= $dom->saveHTML(($f));
    }
    @$dom->loadHTML($html);
    $classname="d-table-cell col-3 col-sm-7 v-align-top pr-3";
    $finder = new DomXPath($dom);
    $spaner = $finder->query("//*[contains(@class, '$classname')]");
    foreach ($spaner as $s) {
        $temp_html = $dom->saveHTML(($s));
        $user = explode("\">" , explode( "href=\"", $temp_html )[1])[0];
        $name = explode("</span>" , explode( "<span class=\"f4 Link--primary\">", $temp_html )[1])[0];
        $followers[ $user ] = $name;
    }
}


// Processing followings:
$followings = [];
$counter = 0;
while (true)
{
    $html = file_get_contents($following_url . "&page=" . ++$counter);
    if ( strpos($html, "reached the end of") !== false ) break;
    @$dom->loadHTML($html);
    $frame = $dom->getElementsByTagName('turbo-frame');
    $html = "";
    foreach ($frame as $f) {
        $html.= $dom->saveHTML(($f));
    }
    @$dom->loadHTML($html);
    $classname="d-table-cell col-3 col-sm-7 v-align-top pr-3";
    $finder = new DomXPath($dom);
    $spaner = $finder->query("//*[contains(@class, '$classname')]");
    foreach ($spaner as $s) {
        $temp_html = $dom->saveHTML(($s));
        $user = explode("\">" , explode( "href=\"", $temp_html )[1])[0];
        $name = explode("</span>" , explode( "<span class=\"f4 Link--primary\">", $temp_html )[1])[0];
        $followings[ $user ] = $name;
    }
}


// var_dump($followers);
// var_dump($followings);

echo "Username: " . PHP_EOL;
echo $username . PHP_EOL;
echo PHP_EOL;

echo "Unfollowers: " . PHP_EOL;
foreach ($followings as $key => $value) {
    if( !isset( $followers[ $key ] ) ) echo $key . " " . $value . PHP_EOL; 
}
echo PHP_EOL;

echo "Fans: " . PHP_EOL;
foreach ($followers as $key => $value) {
    if( !isset( $followings[ $key ] ) ) echo $key . " " . $value . PHP_EOL; 
}


?>
