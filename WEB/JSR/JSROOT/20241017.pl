#!/usr/bin/perl
use CGI::Carp qw(fatalsToBrowser);
use CGI;
use strict;
use warnings;

# URLからdefaultの部分を抽出
my $url = $ENV{'REQUEST_URI'} || '';
my ($default) = $url =~ m|/USR/([^/]+)/WEB/|;
#$default ||= 'default';  # デフォルト値を設定

my $cgi = CGI->new;
print $cgi->header('text/html');

# Get the runNo/Name from the query string
my $hist_or_tree = $cgi->param('hist_or_tree') || 'HIST';
my $runNo = $cgi->param('runNo') || '';
my $runName = $cgi->param('runName') || '';

# Define the directory path and construct the file name
my $dir = "/fuji/EXP/RIBF/TRIP/2024/AUTUMN/USR/$default/$hist_or_tree/";
my $file = "${runName}${runNo}.root";

# Output the HTML
print << "HTML";
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>Read a ROOT file</title>
    <link rel="shortcut icon" href="img/RootIcon.ico"/>
    <script type="text/javascript" src="/fuji/JSROOT/scripts/JSRootCore.js?gui"></script>
</head>
<body>
    <div id="simpleGUI" path="$dir" files="$file"></div>
    <p>Opening file: $file</p>
</body>
</html>
HTML
