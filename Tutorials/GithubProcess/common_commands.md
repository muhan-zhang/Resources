## Common git commands:
  0. `git clone <https://github.com/some_repo/some_repo.git>` Obtain exact copy of repo from github
  1. `git add <file>` Adds local file to git tracking
  2. `git log` Shows local history of commits
  3. `git status` Shows any changes to local files, in addition to any untracked files
  4. `git commit -m "text message"` Commits any files that have been added to stage with message
  5. `git commit -a` Adds then commits all changes in tracked files
  6. `git pull <remote> <branch>` Merges github history to local, taken from remote (usually origin) and branch (often master).
  7. `git push <remote> <branch>` Moves local commits to github repository at remote/branch
  8. `git checkout -b <branch_name>` Makes a new branch and switch to it
  9. `git checkout <branch_name>` Move to branch_name
  10. `git branch` Lists branches, shows which branch you are on
  11. `git branch -d` Delete branch locally
  12. `git push <remote> :<branch_name>` Deletes branch on remote.
  13. `git checkout <file>` Reverts any changes in `file` to state determined by current git hash
  14. `git init` Create a new git repository
  15. `git remote add origin <server>` Connects repository to a remote server
  16. `git diff` View all local changes relative to remote
