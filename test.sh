
#!/bin/bash

echo "🔁 Running tests..."

# Couleurs
GREEN="\033[0;32m"
RED="\033[0;31m"
NC="\033[0m" # No Color

# Compteurs
passed=0
failed=0

# Fonction de test
run_test() {
    description="$1"
    cmd="$2"
    expected="$3"

    ./minishell <<< "$cmd" > minishell_output.txt 2>&1
    bash_output=$(bash -c "$cmd" 2>&1)

    if grep -qF "$expected" minishell_output.txt; then
        echo -e "${GREEN}✅ $description${NC}"
        ((passed++))
    else
        echo -e "${RED}❌ $description${NC}"
        echo "    ↳ Commande : $cmd"
        echo "    ↳ Attendu : $expected"
        echo "    ↳ Obtenu :"
        cat minishell_output.txt
        ((failed++))
    fi
}

# ===== TESTS =====

## Redirection
run_test "Redirection simple" "echo 'Hello World' > test_file && cat test_file" "Hello World"
run_test "Redirection d'entrée" "cat < test_file" "Hello World"
run_test "Redirection d'erreur" "ls non_existent_file 2> error_file && cat error_file" "No such file or directory"
run_test "Redirection de sortie et d'erreur" "ls non_existent_file > all_output 2>&1 && cat all_output" "No such file or directory"
run_test "Redirection vers /dev/null" "echo 'This will not be seen' > /dev/null && echo 'Visible'" "Visible"

## Append
run_test "Append simple" "echo 'First Line' > append_file && echo 'Second Line' >> append_file && cat append_file" "Second Line"
run_test "Append multiple fois" "echo 'Third Line' >> append_file && cat append_file" "Third Line"
run_test "Append avec redirection d'erreur" "ls non_existent_file >> append_file 2>&1 && cat append_file" "No such file or directory"
run_test "Append vers /dev/null" "echo 'Invisible Line' >> /dev/null && echo 'Visible Line'" "Visible Line"
run_test "Append avec commande vide" ">> append_file && echo 'Done'" "Done"

## Heredoc
run_test "Heredoc simple" "cat << EOF
Line 1
Line 2
EOF" "Line 2"
run_test "Heredoc avec variables" "VAR='Test' && cat << EOF
\$VAR
EOF" "Test"
run_test "Heredoc sans expansion" "VAR='Test' && cat << 'EOF'
\$VAR
EOF" "\$VAR"
run_test "Heredoc avec commande" "cat << EOF | grep Line
Line 1
Line 2
EOF" "Line 2"
run_test "Heredoc avec redirection" "cat << EOF > heredoc_file
Line A
Line B
EOF
cat heredoc_file" "Line B"

## Pipe
run_test "Pipe simple" "echo 'Pipe Test' | cat" "Pipe Test"
run_test "Pipe multiple" "echo 'Line1' | grep Line | wc -l" "1"
run_test "Pipe avec redirection" "echo 'Redirected' | tee pipe_file && cat pipe_file" "Redirected"
run_test "Pipe avec commande inexistante" "echo 'Test' | nonexistent_command" "command not found"
run_test "Pipe avec erreur" "ls non_existent_file | cat" "No such file or directory"

# Résumé final
total=$((passed + failed))
echo -e "\n📋 Résumé: ${GREEN}$passed réussis${NC} / ${RED}$failed échoués${NC} (total: $total)"

# Nettoyage
rm -f test_file error_file all_output append_file heredoc_file pipe_file minishell_output.txt

