#!/bin/bash

# ROOTファイルのプレフィックスを抽出してリストを表示
get_prefixes() {
    ls ./ROOT/*.root | sed -E 's|.*/(.*)[0-9]{4}\.root|\1|' | sort -u
}

# 選択されたプレフィックスに基づいてファイルリストを表示
show_files() {
    local prefix=$1
    ls ./ROOT/${prefix}*.root
}

# ROOTファイルの結合を実行
hadd_files() {
    local output_file=$1
    shift
    hadd "$output_file" "$@"
    echo "結合したファイル: $output_file"
}

# メインループ
while true; do
    echo "ROOTファイルのプレフィックスのリスト："
    mapfile -t prefixes < <(get_prefixes)
    select prefix in "${prefixes[@]}" "終了"; do
        if [ "$prefix" = "終了" ]; then
            exit 0
        elif [ -n "$prefix" ]; then
            echo "ファイルリスト："
            mapfile -t files < <(show_files "$prefix")
            printf "以下のファイルがあります:\n"
            printf "%s\n" "${files[@]}"

	    echo ""
            echo "haddを実行する方法を選んでください："
            select method in "連番" "自由指定"; do
                case $method in
                    "連番")
                        echo "開始するrunNoを入力してください:"
                        read runNo_start
                        echo "終了するrunNoを入力してください:"
                        read runNo_stop

                        # デフォルトの出力ファイル名を生成
                        default_output="./ROOT/MERGED/${runNo_start}_${runNo_stop}.root"
                        echo "出力ファイル名を指定してください (デフォルト: ${default_output}):"
                        read custom_name
                        output_file="./ROOT/MERGED/${custom_name:-${runNo_start}_${runNo_stop}}.root"

                        files_to_merge=()
                        for ((runNo=runNo_start; runNo<=runNo_stop; runNo++)); do
                            files_to_merge+=("./ROOT/${prefix}$(printf '%04d' $runNo).root")
                        done

                        # haddの実行
                        hadd_files "$output_file" "${files_to_merge[@]}"
                        break
                        ;;
                    "バラバラ")
                        echo "結合したいファイルの番号をカンマで区切って入力してください（例: 1, 2, 4, 7, 8）:"
                        read indices
                        IFS=',' read -ra idx_array <<< "$indices"
                        files_to_merge=()
                        for i in "${idx_array[@]}"; do
                            files_to_merge+=("${files[$((i - 1))]}")  # 配列は0から始まるため1を引く
                        done

                        # デフォルトの出力ファイル名を生成
                        default_output="./ROOT/MERGED/merged_random.root"
                        echo "出力ファイル名を指定してください (デフォルト: ${default_output}):"
                        read custom_name
                        output_file="./ROOT/MERGED/${custom_name:-merged_random}.root"

                        # hadding the specified files
                        hadd_files "$output_file" "${files_to_merge[@]}"
                        break
                        ;;
                    *) echo "無効な選択です。再度選んでください。" ;;
                esac
            done
            break
        else
            echo "無効な選択です。再度選んでください。"
        fi
    done
done

