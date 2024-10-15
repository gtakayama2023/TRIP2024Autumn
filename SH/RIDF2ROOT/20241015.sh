#!/bin/bash

# ファイルのプレフィックスを抽出してリストを表示
get_prefixes() {
    ls ./RIDF/*.ridf | sed -E 's/.*\/(.*[^0-9])[0-9]+\.ridf/\1/' | sort -u
}

# 選択されたプレフィックスに基づいてファイルリストを表示
show_files() {
    local prefix=$1
    ls ./RIDF/${prefix}*.ridf
}

# ファイルからヘッダーとrunNoを抽出
extract_info() {
    local file=$1
    local header=$(echo "$file" | sed -E 's/.*\/(.*[^0-9])[0-9]+\.ridf/\1/')
    local runNo=$(echo "$file" | sed -E 's/.*[^0-9]([0-9]+)\.ridf/\1/')

    # runNo を数字に変換
    runNo=$(echo "$runNo" | sed 's/^0*//')  # 先頭のゼロを削除

    echo "Header: $header, RunNo: $runNo"

    # root コマンドの実行
    root -l -b -q './ANA/ridf2root.cpp++g('$runNo', "'$header'")'
}

# メインループ
while true; do
    echo "プレフィックスのリスト："
    mapfile -t prefixes < <(get_prefixes)
    select prefix in "${prefixes[@]}" "終了"; do
        if [ "$prefix" = "終了" ]; then
            exit 0
        elif [ -n "$prefix" ]; then
            echo "ファイルリスト："
            mapfile -t files < <(show_files "$prefix")
            select file in "${files[@]}" "戻る"; do
                if [ "$file" = "戻る" ]; then
                    break
                elif [ -n "$file" ]; then
                    extract_info "$file"
                    break
                else
                    echo "無効な選択です。再度選んでください。"
                fi
            done
            break
        else
            echo "無効な選択です。再度選んでください。"
        fi
    done
done

