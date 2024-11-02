<?php
// CSVファイルのパス
$csvFile = '/home/exp/EXP/RIBF/TRIP/2024/AUTUMN/USR/default/RIDF/runsummary.csv';

// 現在のURLからサブディレクトリを取得
$currentUrl = $_SERVER['REQUEST_URI'];
$pathParts = explode('/', trim($currentUrl, '/'));
$subDir = 'default'; // デフォルト値を設定
$base_url = 'fuji';

// URLのパスから適切なサブディレクトリを取得
if (count($pathParts) > 6) {
    $subDir = $pathParts[6]; // gen などのサブディレクトリを取得
}

// ファイルを開く
if (($handle = fopen($csvFile, 'r')) !== false) {
    // ヘッダー行を読み込む
    $headers = fgetcsv($handle, 1000, ',', '"');

    // ヘッダーに ridf2root と JSROOT を追加
    array_unshift($headers, 'rsync', 'RIDF2TREE @Fuji', 'RIDF2HIST @gtn009', 'JSROOT');

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
	    .update_button {
	        display: inline-block;
	        padding: 10px 20px;
	        font-size: 16px;
	        color: white;
	        background-color: #4CAF50; /* ボタンの色 */
	        border: none;
	        border-radius: 5px; /* 角を丸く */
	        text-align: center;
	        text-decoration: none; /* 下線を消す */
	        transition: background-color 0.3s, transform 0.3s; /* ホバー効果のトランジション */
	    }
	    
	    .update_button:hover {
	        background-color: #45a049; /* ホバー時の色 */
	        transform: scale(1.05); /* ホバー時のサイズ変更 */
	    }
	    .exe-button {
	        background-color: #EB9899; /* 薄い赤色 */
	        border: none;
	        color: white;
	        padding: 1px 2px;
	        text-align: center;
	        text-decoration: none;
	        display: inline-block;
	        font-size: 16px;
	        margin: 1px 2px;
	        transition-duration: 0.4s;
	        cursor: pointer;
	        border-radius: 4px;
	    }
	    .exe-button:hover {
	        background-color: white;
	        color: black;
	        border: 2px solid #EB9899;
	    }
	    .button {
	        display: inline-block;
	        padding: 10px 20px;
	        font-size: 16px;
	        color: white;
	        background-color: #4CAF50; /* ボタンの色 */
	        border: none;
	        border-radius: 5px; /* 角を丸く */
	        text-align: center;
	        text-decoration: none; /* 下線を消す */
	        transition: background-color 0.3s, transform 0.3s; /* ホバー効果のトランジション */
	    }
	    .cool-button:hover {
	        background-color: white;
	        color: black;
	        border: 2px solid #4CAF50;
	    }
          </style>";

    // タイトルとリンクを表示
    echo "<h2>TRIP-S3CAN 2024秋 取得データの一覧 ( ユーザー: $subDir )</h2>";
    #echo "<p><a href='/$base_url/cgi-bin/EXP/RIBF/TRIP/2024/AUTUMN/USR/$subDir/RIDF/runsummary.sh' style='color: #4CAF50; text-decoration: none;'>Update runsummary</a></p>";
    echo "<div style='display: flex; justify-content: center; align-items: center;'>
              <a href='/$base_url/EXP/RIBF/TRIP/2024/AUTUMN/USR/$subDir/WEB/index.php' class='update_button' style='margin-right: 20px;'>ホーム</a>
              <a href='/$base_url/cgi-bin/EXP/RIBF/TRIP/2024/AUTUMN/USR/$subDir/WEB/rsync_full' class='update_button' style='margin-right: 20px;'>rsync (gtn000 → gtn009 → Fuji)</a>
              <a href='/$base_url/cgi-bin/EXP/RIBF/TRIP/2024/AUTUMN/USR/default/RIDF/gtn000to009' class='update_button' style='margin-right: 20px;'>rsync (gtn000 → gtn009)</a>
              <a href='/$base_url/cgi-bin/EXP/RIBF/TRIP/2024/AUTUMN/USR/$subDir/RIDF/runsummary.sh' class='update_button' style='margin-right: 20px;'>一覧表の更新</a>
              <a href='https://docs.google.com/spreadsheets/d/1RUte0R5B9rzbLZ0xoQrSmysUAloWTyCzLD17C4qUaBs/edit?usp=sharing' class='update_button'>Run summary (Google Sheet)</a>
          </div>";


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

        //// ridf2root URLを最初の列に追加
        //echo "<td><a href='/$base_url/cgi-bin/EXP/RIBF/TRIP/2024/AUTUMN/USR/$subDir/ridf2root?runNo=$runNumber&runName=" . urlencode($runName) . "' target='_blank'>ridf2root</a></td>";

	// ridf2root URLをボタンに置き換え、数値に変換してURLを作成
	$loadEvts = ['10k' => 10000, '100k' => 100000, '1M' => 1000000, '1G' => 1000000000];
	
	// 現在のURLを取得
	$currentUrl = $_SERVER['PHP_SELF'];

	echo "<td>";
	echo "<button class='cool-button' type='button' onclick=\"window.open('/$base_url/cgi-bin/EXP/RIBF/TRIP/2024/AUTUMN/USR/$subDir/WEB/rsync_each?runNo=$runNumber&runName=" . urlencode($runName) . "', '_blank')\">rsync</button> ";
	echo "</td>";
	
	echo "<td>";
	if (strpos($currentUrl, 'ridf.php') !== false) {
	    // ridf.phpの場合、「10k」ボタンのみを表示
	    echo "<button class='exe-button' type='button' onclick=\"window.open('/$base_url/cgi-bin/EXP/RIBF/TRIP/2024/AUTUMN/USR/$subDir/web_ridf2root?runNo=$runNumber&runName=" . urlencode($runName) . "&loadEvts=" . $loadEvts['10k'] . "', '_blank')\">10k</button> ";
	} elseif (strpos($currentUrl, 'ridf.auth.php') !== false) {
	    // ridf.auth.phpの場合、全ボタンを表示
	    foreach ($loadEvts as $label => $value) {
	        echo "<button class='exe-button' type='button' onclick=\"window.open('/$base_url/cgi-bin/EXP/RIBF/TRIP/2024/AUTUMN/USR/$subDir/web_ridf2root?runNo=$runNumber&runName=" . urlencode($runName) . "&loadEvts=$value', '_blank')\">$label</button> ";
	    }
	}
	echo "</td>";

	echo "<td>";
	if (strpos($currentUrl, 'ridf.php') !== false) {
	    // ridf.phpの場合、「10k」ボタンのみを表示
	    echo "<button class='exe-button' type='button' onclick=\"window.open('/$base_url/cgi-bin/EXP/RIBF/TRIP/2024/AUTUMN/USR/$subDir/WEB/ridf2hist?runNo=$runNumber&runName=" . urlencode($runName) . "&loadEvts=" . $loadEvts['10k'] . "', '_blank')\">10k</button> ";
	} elseif (strpos($currentUrl, 'ridf.auth.php') !== false) {
	    // ridf.auth.phpの場合、全ボタンを表示
	    foreach ($loadEvts as $label => $value) {
	        echo "<button class='exe-button' type='button' onclick=\"window.open('/$base_url/cgi-bin/EXP/RIBF/TRIP/2024/AUTUMN/USR/$subDir/WEB/ridf2hist?runNo=$runNumber&runName=" . urlencode($runName) . "&loadEvts=$value', '_blank')\">$label</button> ";
	    }
	}
	echo "</td>";

	// JSROOT URLを次の列に追加し、HISTとTREEをボタンに置き換え
	echo "<td>";
	echo "<button class='cool-button' type='button' onclick=\"window.open('/$base_url/cgi-bin/EXP/RIBF/TRIP/2024/AUTUMN/USR/$subDir/WEB/JSR/jsroot.pl?runNo=$runNumber&runName=" . urlencode($runName) . "', '_blank')\">HIST</button> ";
	echo "<button class='cool-button' type='button' onclick=\"window.open('/$base_url/cgi-bin/EXP/RIBF/TRIP/2024/AUTUMN/USR/$subDir/WEB/JSR/jsroot.pl?hist_or_tree=ROOT&runNo=$runNumber&runName=" . urlencode($runName) . "', '_blank')\">TREE</button>";
	echo "</td>";

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

