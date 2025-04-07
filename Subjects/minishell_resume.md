# 🐚 Minishell — Résumé Synthétique

## 🛠️ Projet : Minishell

Crée ton propre shell, façon mini-Bash.  
Objectif : comprendre **processus**, **fds**, **pipes**, **signaux**, **environnement**.  
Résultat attendu : un shell interactif comme Bash, mais codé par toi.

---

## ✅ Partie Obligatoire

### 🖥️ Fonctionnalités

- Prompt (`minishell$ `)
- Historique (grâce à `readline`)
- Exécution de binaires via `PATH`
- Redirections : `<`, `>`, `<<`, `>>`
- Pipes : `|`
- Variables env : `$VAR`, `$?`
- Quotes :
  - `'` → aucune interprétation
  - `"` → interpolation du `$` seulement
- Signaux :
  - `Ctrl-C` → prompt propre
  - `Ctrl-D` → quitter
  - `Ctrl-\` → rien

### 🔧 Builtins à coder

| Commande | Spécificité |
|----------|-------------|
| `echo`   | supporte `-n` |
| `cd`     | chemin relatif/absolu |
| `pwd`    | aucun argument |
| `export` | pas d'option |
| `unset`  | pas d'option |
| `env`    | pas d’option |
| `exit`   | sans option |

### 📌 Règles Clés

- 1 seule **variable globale** (pour signaux)
- **Aucune fuite mémoire** dans ton code
- Norme respectée partout
- `Makefile` propre : `all`, `clean`, `fclean`, `re`, `bonus`
- `libft` autorisée (copiée dans `./libft`)

---

## 🎁 Partie Bonus

> ⚠️ Activée *uniquement si* la partie obligatoire est **100% clean**.

- `&&`, `||` avec **parenthèses**
- Wildcards `*` (fichiers du dossier courant)

---

## 💡 Conseils

- Teste **tout** (scripts, erreurs, signaux, edge-cases)
- Réfère-toi à **bash** pour les comportements ambigus
- Ne code **que ce qui est demandé**. Pas plus.