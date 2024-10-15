<?php
$title = "TRIP-S3CAN 2024Autumn Analysis Platform";
$urls = [
    "/EXP/RIBF/TRIP/2024/AUTUMN/USR/default/WEB/ridf.php",
    "/EXP/RIBF/TRIP/2024/AUTUMN/USR/default/WEB/SKD/index.auth.php",
    "/EXP/RIBF/TRIP/2024/AUTUMN/USR/default/WEB/SKD/table.php",
    "/EXP/RIBF/TRIP/2024/AUTUMN/USR/default/WEB/LISE/HTML/"
];
?>

<!DOCTYPE html>
<html lang="ja">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title><?php echo $title; ?></title>
</head>
<body>
    <h1><?php echo $title; ?></h1>
    <ul>
        <?php foreach ($urls as $url): ?>
            <li><a href="<?php echo $url; ?>"><?php echo $url; ?></a></li>
        <?php endforeach; ?>
    </ul>
</body>
</html>

