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
    root -l -b -q './ANA/ridf2root.cpp++g('$runNo', "'$header'", '$tree_output', '$loadEvt')'
}

# multiple ファイルの処理
extract_multiple() {
    local prefix=$1
    local runNo_start=$2
    local runNo_stop=$3

    for ((runNo=runNo_start; runNo<=runNo_stop; runNo++)); do
        local file="./RIDF/${prefix}$(printf '%04d' $runNo).ridf"
        if [ -f "$file" ]; then
            extract_info "$file"
        else
            echo "$file は存在しません。"
        fi
    done
}

# メインループ
while true; do
    echo "プレフィックスのリスト："
    mapfile -t prefixes < <(get_prefixes)
    select prefix in "${prefixes[@]}" "終了"; do
        if [ "$prefix" = "終了" ]; then
            exit 0
        elif [ -n "$prefix" ]; then
	    echo ""
            echo "tree に書き出しますか？"
            select tree_choice in "yes" "no"; do
                case $tree_choice in
                    "yes") tree_output=true; break ;;
                    "no") tree_output=false; break ;;
                    *) echo "無効な選択です。再度選んでください。" ;;
                esac
            done

	    echo ""
            echo "single か multiple を選んでください："
            select choice in "single" "multiple"; do
		echo ""
                echo "ロードするイベント数を選んでください："
                select load_option in "10k" "100k" "1M" "1G" "好きな数字"; do
                    case $load_option in
                        "10k") loadEvt=10000; break ;;
                        "100k") loadEvt=100000; break ;;
                        "1M") loadEvt=1000000; break ;;
                        "1G") loadEvt=1000000000; break ;;
                        "好きな数字") 
                            echo "数字を入力してください:"
                            read loadEvt
                            break 
                            ;;
                        *) echo "無効な選択です。再度選んでください。" ;;
                    esac
                done

                if [[ "$choice" == "single" ]]; then
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
                elif [[ "$choice" == "multiple" ]]; then
		    echo ""
                    echo "開始するrunNoを入力してください:"
                    read runNo_start
                    echo "終了するrunNoを入力してください:"
                    read runNo_stop
                    extract_multiple "$prefix" "$runNo_start" "$runNo_stop"
                else
                    echo "無効な選択です。再度選んでください。"
                fi
                break
            done
            break
        else
            echo "無効な選択です。再度選んでください。"
        fi
    done
done

