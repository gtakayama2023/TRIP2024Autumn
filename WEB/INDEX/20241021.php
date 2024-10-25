<?php
// 現在のリクエストURIから`$usr_name`を抽出する
$uri = $_SERVER['REQUEST_URI'];
preg_match('/\/USR\/(.*?)\/WEB\//', $uri, $matches);
$usr_name = $matches[1] ?? 'default'; // マッチしなかった場合は 'default' をデフォルトに

$title = "TRIP-S3CAN 2024秋 解析プラットフォーム (ユーザー: {$usr_name})";

// 各リンクの名前とURLを設定
$urls = [
    "/fuji/EXP/RIBF/TRIP/2024/AUTUMN/USR/index.php" => "ユーザー選択",
    "/fuji/EXP/RIBF/TRIP/2024/AUTUMN/USR/{$usr_name}/WEB/ridf.php" => "取得データの一覧",
    "/fuji/EXP/RIBF/TRIP/2024/AUTUMN/USR/{$usr_name}/WEB/SKD/table.php" => "測定メニュー",
    "/fuji/EXP/RIBF/TRIP/2024/AUTUMN/USR/{$usr_name}/WEB/SKD/index.auth.php" => "測定メニュー管理",
    "/fuji/EXP/RIBF/TRIP/2024/AUTUMN/USR/{$usr_name}/WEB/LISE/HTML/" => "LISE++ 設定一覧",
    "/fuji_jn/doc/tree/EXP/RIBF/TRIP/2024/AUTUMN/USR/{$usr_name}/WEB/JPY/" => "Jupyter ( 上級者向け )",
    "/fuji/EXP/RIBF/TRIP/2024/AUTUMN/USR/{$usr_name}/WEB/Ge_calc/source.html" => "Ge 検出器計算ツール",
];
?>

<!DOCTYPE html>
<html lang="ja">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title><?php echo $title; ?></title>
    <style>
        body {
            font-family: 'Arial', sans-serif;
            background-color: #f4f4f9;
            color: #333;
            margin: 0;
            padding: 0;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
        }
        h1 {
            text-align: center;
            color: #2c3e50;
            font-size: 2.5rem;
            margin-bottom: 20px;
        }
        ul {
            list-style: none;
            padding: 0;
            margin: 0;
            text-align: center;
        }
        li {
            margin: 10px 0;
        }
        a {
            text-decoration: none;
            font-size: 1.2rem;
            color: #3498db;
            background-color: #ecf0f1;
            padding: 10px 20px;
            border-radius: 25px;
            transition: all 0.3s ease;
        }
        a:hover {
            background-color: #3498db;
            color: white;
        }
        @media (max-width: 600px) {
            h1 {
                font-size: 2rem;
            }
            a {
                font-size: 1rem;
            }
        }
    </style>
</head>
<body>
    <div>
        <h1><?php echo $title; ?></h1>
	<div style="text-align: center;">
	    <a href="https://ribf.riken.jp/~takayama/s3can/doku.php?id=trip-s3can:2024autum:linkssummary">wiki</a>
	</div>
	<ul>
        <ul>
            <?php foreach ($urls as $url => $name): ?>
                <li><a href="<?php echo $url; ?>"><?php echo $name; ?></a></li>
            <?php endforeach; ?>
        </ul>
    </div>
</body>
</html>

