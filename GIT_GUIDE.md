# miniRT — Git Guide

---

## Branch structure

```
main                        ← stable releases only, never push here directly
└── dev                     ← shared integration branch
    ├── feat/parser         ← scene file parsing module
    │   ├── parser/objects  ← sphere, plane, cylinder
    │   └── parser/camera   ← viewport, FOV
    ├── feat/rendering      ← ray casting & intersections
    │   ├── render/rays     ← ray origin & direction
    │   └── render/intersect← hit detection math
    └── feat/lighting       ← lights, shading, shadows
        ├── light/ambient
        └── light/diffuse
```

**Flow:** `sub-branch` → `feat/` → PR → `dev` → PR → `main`

Merges into `feat/` branches are open — no PR required, but give your partner a heads up before merging. Merges into `dev` and `main` always require a reviewed PR.

---

## Daily workflow

### 1. Start a task
Always branch off the relevant `feat/` branch — never off `main` or `dev`:
```bash
git checkout feat/parser
git pull origin feat/parser      # sync before branching
git checkout -b parser/camera    # your new sub-branch
```

### 2. Work and commit
Commit small and often:
```bash
git add src/parser.c includes/parser.h
git commit -m "feat: parse camera FOV and position from .rt"
```

Commit prefixes to use:

| Prefix | When |
|---|---|
| `feat:` | New functionality |
| `fix:` | Bug fix |
| `refactor:` | Restructure without behaviour change |
| `test:` | Adding or updating tests |
| `chore:` | Makefile, config, housekeeping |

### 3. Push and merge into feat/
```bash
git push origin parser/camera
git checkout feat/parser
git merge parser/camera
git push origin feat/parser
git branch -d parser/camera                    # clean up local
git push origin --delete parser/camera         # clean up remote
```

No PR needed here — but let your partner know before merging.

### 4. Open a PR into dev
Once a `feat/` branch is stable and complete, go to GitHub: **Pull requests → New pull request**
- base: `dev` ← compare: `feat/parser`
- Request your partner as reviewer
- Once approved → **Squash and merge**

### 5. Promote dev → main via PR
When all features are integrated and tested in `dev`:
- base: `main` ← compare: `dev`
- Partner approves → **Squash and merge**

### 6. Sync every morning
Before touching anything, pull the latest from your feat branch:
```bash
git checkout dev && git pull origin dev
git checkout feat/parser && git pull origin feat/parser
```

---

## Cheat guide — common situations

### See what's going on
```bash
git status                        # what files changed / staged
git log --oneline                 # compact commit history
git log --oneline --graph --all   # visual tree of all branches
git diff                          # unstaged changes
git diff --staged                 # staged changes ready to commit
```

### Undo things

| Situation | Command |
|---|---|
| Unstage a file (keep changes) | `git restore --staged <file>` |
| Discard changes in a file | `git restore <file>` |
| Undo last commit (keep changes staged) | `git reset --soft HEAD~1` |
| Undo last commit (keep changes unstaged) | `git reset HEAD~1` |
| Completely discard last commit ⚠️ | `git reset --hard HEAD~1` |
| Revert a commit already pushed | `git revert <commit-hash>` |

> `reset --hard` is destructive — use `revert` instead when the commit is already on the remote.

### Branches

```bash
git branch                        # list local branches
git branch -a                     # list all branches including remote
git branch -d feat/parser         # delete branch (safe — only if merged)
git branch -D feat/parser         # delete branch (force)
git checkout -                    # switch to previous branch
```

### Syncing with your partner

```bash
git fetch --all                   # download remote changes without merging
git pull origin feat/rendering    # fetch + merge a specific branch
git merge feat/rendering          # merge that branch into your current one
```

### Resolving merge conflicts
When Git tells you there's a conflict, open the file and find:
```
<<<<<<< HEAD
your version of the code
=======
your partner's version
>>>>>>> feat/rendering
```
Edit the file to the correct final state, remove the markers, then:
```bash
git add <conflicted-file>
git commit -m "fix: resolve merge conflict with rendering types"
```

To abort a merge mid-way and go back to before:
```bash
git merge --abort
```

### Stashing — save work without committing
Useful when you need to switch branches but aren't ready to commit:
```bash
git stash                         # save current changes aside
git stash pop                     # restore them
git stash list                    # see all stashes
git stash drop                    # discard the latest stash
```

### Finding a bug with bisect
When something broke and you don't know which commit caused it:
```bash
git bisect start
git bisect bad                    # current state is broken
git bisect good <commit-hash>     # last known good commit
# Git checks out a middle commit — test it, then:
git bisect good                   # or: git bisect bad
# Repeat until Git identifies the culprit commit
git bisect reset                  # exit bisect mode
```

### Inspecting a specific commit
```bash
git show <commit-hash>            # see changes introduced by a commit
git blame <file>                  # see who last changed each line
```

---

## Golden rules

1. **Never push directly to `main` or `dev`** — always go through a PR.
2. **Always pull before branching** — stale base = guaranteed conflicts.
3. **Never merge your own PR** — your partner reviews first.
4. **Delete sub-branches after merging** — keeps the branch list clean.
5. **One logical change per commit** — makes `git bisect` and reviews much easier.