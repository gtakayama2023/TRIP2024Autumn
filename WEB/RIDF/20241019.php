<?php
// CSVファイルのパス
$csvFile = '/home/exp/EXP/RIBF/TRIP/2024/AUTUMN/USR/default/RIDF/runsummary.csv';

// 現在のURLからサブディレクトリを取得
$currentUrl = $_SERVER['REQUEST_URI'];
$pathParts = explode('/', trim($currentUrl, '/'));
$subDir = 'default'; // デフォルト値を設定

// URLのパスから適切なサブディレクトリを取得
if (count($pathParts) > 6) {
    $subDir = $pathParts[6]; // gen などのサブディレクトリを取得
}

// ファイルを開く
if (($handle = fopen($csvFile, 'r')) !== false) {
    // ヘッダー行を読み込む
    $headers = fgetcsv($handle, 1000, ',', '"');

    // ヘッダーに ridf2root と JSROOT を追加
    array_unshift($headers, 'ridf2root (10k)', 'JSROOT');

    // CSSスタイルの追加
    echo "<style>
            body {
                font-family: Arial, sans-serif;
                background-color: #f4f4f4;
                margin: 0;
                padding: 20px;
            }
            h2 {
                text-align: center;
                font-size: 36px;
                color: #333;
                margin-bottom: 20px;
                padding: 10px;
                background-color: #4CAF50;
                color: white;
                border-radius: 5px;
                box-shadow: 0 2px 10px rgba(0, 0, 0, 0.1);
            }
            p {
                text-align: center;
                margin: 20px 0;
            }
            table {
                width: 100%;
                border-collapse: collapse;
                margin: 20px 0;
                font-size: 16px;
                text-align: left;
                box-shadow: 0 2px 10px rgba(0, 0, 0, 0.1);
            }
            th, td {
                padding: 10px;
                border: 1px solid #ddd;
            }
            th {
                background-color: #4CAF50;
                color: white;
            }
            tr:nth-child(even) {
                background-color: #f2f2f2;
            }
            tr:hover {
                background-color: #ddd;
            }
            input[type='text'] {
                width: 100%;
                padding: 8px;
                margin: 5px 0 10px;
                border: 1px solid #ccc;
                border-radius: 4px;
            }
          </style>";

    // タイトルとリンクを表示
    echo "<h2>ridf data list ( TRIP-S3CAN 2024 Autumn )</h2>";
    echo "<p><a href='/cgi-bin/EXP/RIBF/TRIP/2024/AUTUMN/USR/default/RIDF/csvruninfo.pl' style='color: #4CAF50; text-decoration: none;'>Update runsummary</a></p>";

    // HTMLテーブルの開始
    echo "<table id='dataTable'>";

    // ヘッダー行を作成
    echo "<tr>";
    foreach ($headers as $index => $header) {
        echo "<th>" . htmlspecialchars($header) . "</th>";
    }
    echo "</tr>";

    // フィルタ入力行を作成
    echo "<tr>";
    foreach ($headers as $index => $header) {
        echo "<td><input type='text' onkeyup='filterTable()' placeholder='Filter by $header' /></td>";
    }
    echo "</tr>";

    // データを読み込む
    while (($data = fgetcsv($handle, 1000, ',', '"')) !== false) {
        echo "<tr>";

        // Run numberを取得
        $runNumber = $data[1]; // Assuming the Run number is in the second column
        // Run nameを取得
        $runName = $data[0]; // Assuming the Run name is in the first column

        // ridf2root URLを最初の列に追加
        echo "<td><a href='/cgi-bin/EXP/RIBF/TRIP/2024/AUTUMN/USR/$subDir/ridf2root?runNo=$runNumber&runName=" . urlencode($runName) . "' target='_blank'>ridf2root</a></td>";

        // JSROOT URLを次の列に追加
        echo "<td><a href='/cgi-bin/EXP/RIBF/TRIP/2024/AUTUMN/USR/$subDir/WEB/JSR/jsroot.pl?runNo=$runNumber&runName=" . urlencode($runName) . "' target='_blank'>JSROOT</a></td>";

        // 残りのデータを出力
        foreach ($data as $cell) {
            echo "<td>" . htmlspecialchars($cell) . "</td>";
        }
        echo "</tr>";
    }

    // HTMLテーブルの終了
    echo "</table>";

    // ファイルを閉じる
    fclose($handle);
} else {
    echo "CSVファイルを開くことができませんでした。\n";
}
?>

<script>
function filterTable() {
    const table = document.getElementById("dataTable");
    const tr = table.getElementsByTagName("tr");
    const filters = Array.from(document.getElementsByTagName("input")).map(input => input.value.trim());

    // 各行をループ
    for (let i = 2; i < tr.length; i++) { // 2から始めてヘッダーとフィルタ行をスキップ
        const tds = tr[i].getElementsByTagName("td");
        let shouldDisplay = true;

        // 各列のフィルタをチェック
        for (let j = 0; j < filters.length; j++) {
            const filterValue = filters[j].toLowerCase();
            if (filterValue && tds[j]) {
                const txtValue = tds[j].textContent || tds[j].innerText;

                // 通常のテキストフィルタ
                if (txtValue.toLowerCase().indexOf(filterValue) === -1) {
                    shouldDisplay = false;
                    break;
                }
            }
        }

        // 行の表示/非表示を設定
        tr[i].style.display = shouldDisplay ? "" : "none";
    }
}
</script>

