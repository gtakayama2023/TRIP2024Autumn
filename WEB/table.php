<?php
// CSVファイルのパス
$csvFile = '/home/exp/EXP/RIBF/TRIP/2024/AUTUMN/USR/default/RIDF/runsummary.csv';

// ファイルを開く
if (($handle = fopen($csvFile, 'r')) !== false) {
    // ヘッダー行を読み込む
    $headers = fgetcsv($handle, 1000, ',', '"');

    // ヘッダーに JSROOT を追加
    array_unshift($headers, 'JSROOT');

    // HTMLテーブルの開始
    echo "<table border='1' cellspacing='0' cellpadding='5' id='dataTable'>";

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
        echo "<td><a href='/cgi-bin/EXP/RIBF/TRIP/2024/AUTUMN/USR/default/WEB/JSR/jsroot.pl?runNo=$runNumber&runName=" . urlencode($runName) . "' target='_blank'>JSROOT</a></td>";

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

                // 数値比較をサポートする
                if (j === 1 || j === 7) { // 1: Run number, 7: Size (MB)
                    const operator = filterValue.charAt(0); // 最初の文字を取得
                    const filterNumber = parseFloat(filterValue.slice(1)); // 演算子を除いた部分を数値として取得
                    const cellNumber = parseFloat(txtValue.replace(/,/g, '').trim()); // セルの値を数値として取得（カンマを削除）

                    // 数値比較を行う
                    if (isNaN(filterNumber) || isNaN(cellNumber) ||
                        (operator === '>' && cellNumber <= filterNumber) ||
                        (operator === '<' && cellNumber >= filterNumber) ||
                        (operator === '=' && cellNumber !== filterNumber)) {
                        shouldDisplay = false;
                        break;
                    }
                } else {
                    // 通常のテキストフィルタ
                    if (txtValue.toLowerCase().indexOf(filterValue) === -1) {
                        shouldDisplay = false;
                        break;
                    }
                }
            }
        }

        // 行の表示/非表示を設定
        tr[i].style.display = shouldDisplay ? "" : "none";
    }
}
</script>

