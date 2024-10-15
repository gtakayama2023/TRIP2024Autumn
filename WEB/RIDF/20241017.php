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

    // ヘッダーに JSROOT を追加
    array_unshift($headers, 'JSROOT');

    // CSSスタイルの追加
    echo "<style>
            table {
                width: 100%;
                border-collapse: collapse;
                margin: 20px 0;
                font-size: 16px;
                text-align: left;
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
        $runName = $data[0]; // Assuming the Run name is in the third column

        // JSROOT URLを最初の列に追加
        echo "<td><a href='/cgi-bin/EXP/RIBF/TRIP/2024/AUTUMN/USR/$subDir/WEB/JSR/jsroot.pl?runNo=$runNumber&runName=" . urlencode($runName) . "' target='_blank'>JSROOT</a></td>";

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

