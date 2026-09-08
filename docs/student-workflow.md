# Student workflow: fork, pull request, and instructor review

Each student keeps one personal fork of this course for the semester. Work on
each lab in a separate branch and submit a pull request (PR) to `master` in
your own fork. The instructor is `@ant112342`.

**A lab is accepted only after the instructor approves its PR. A push or merge
alone does not count as acceptance.** Keep the review rules enabled throughout
the course and request another review after changing reviewed code.

## 1. Create and clone your fork

On [the course repository](https://github.com/ant112342/embedded-linux-course),
click **Fork** and choose your personal account. Keep the repository name
`embedded-linux-course` and the default branch `master`.

On HOST, replace `YOUR-GITHUB-USERNAME` with your GitHub username:

```bash
git clone https://github.com/YOUR-GITHUB-USERNAME/embedded-linux-course.git
cd embedded-linux-course
git remote add upstream https://github.com/ant112342/embedded-linux-course.git
git remote -v
```

`origin` must point to your fork; `upstream` must point to the instructor's
repository. Use this same clone for all labs. The kernel workspace remains
outside it at `~/bbb-workspace`; see [the workspace guide](course-workspace.md).

## 2. Set up instructor review in your fork

Complete this once before starting Lab 01:

1. In your fork, open **Settings → Collaborators** and invite `ant112342`.
   Wait for the instructor to accept. Code owners need write access to the
   repository; naming someone in a file does not grant access.
2. On `master` in your fork, create `.github/CODEOWNERS` with this content and
   commit it as the initial review setup:

   ```text
   * @ant112342
   ```

3. Open **Settings → Branches** and add a classic branch protection rule for
   the branch name pattern `master`. Enable:
   - **Require a pull request before merging**;
   - **Require approvals**, with **1** required approval;
   - **Require review from Code Owners**, so the instructor must approve;
   - **Dismiss stale pull request approvals when new commits are pushed**;
   - **Do not allow bypassing the above settings**, so the rule also applies
     to you as the fork owner.
4. Keep force pushes and branch deletions disabled. Save the rule and send the
   instructor your fork's URL so they can check access and the setup.

The rule blocks merges and direct pushes to `master` while it is enabled.
As the owner of a personal fork, you can still edit or remove its protection
settings. This setup therefore also relies on the course rule: disabling
protection or merging without instructor approval does not earn lab credit.

These settings are available for public forks on GitHub Free. See GitHub's
[branch protection documentation](https://docs.github.com/en/repositories/configuring-branches-and-merges-in-your-repository/managing-protected-branches/managing-a-branch-protection-rule)
and [CODEOWNERS documentation](https://docs.github.com/en/repositories/managing-your-repositorys-settings-and-features/customizing-your-repository/about-code-owners).

## 3. Work on one lab branch

After completing the review setup, start Lab 01 from the root of your clone:

```bash
git checkout master
git pull --ff-only origin master
git checkout -b lab01
cd classroom-templates/lab01-board-bringup
```

Follow the lab README in this directory. Edit `src/hello.c` and any required
Makefile changes, then fill in `report.md` with your own BBB evidence.
`classroom-templates/` is the folder containing lab instructions and starter
files; students complete those files in their own forks.

From the Lab 01 directory, commit and push your work:

```bash
git status --short
git add src/hello.c Makefile report.md
git diff --cached
git commit -m "labs: Complete lab01 board bringup task"
git push -u origin lab01
```

Commit source and reports. Do not commit downloaded images, kernel sources,
toolchains, passwords, or generated build output such as `.ko` and `.o` files.
For Lab 02, use branch `lab02` and directory
`classroom-templates/lab02-first-kernel-module` in the same way.

## 4. Open the submission PR in your own fork

In your fork, open **Pull requests → New pull request**. GitHub may suggest
the instructor's repository as the destination. Check both repository selectors
and set them explicitly:

```text
base repository:    YOUR-GITHUB-USERNAME/embedded-linux-course
base branch:        master
head repository:    YOUR-GITHUB-USERNAME/embedded-linux-course
compare branch:     lab01
```

The PR must merge your lab branch into your fork's `master`. Send course
material corrections to the instructor's repository only when requested.

Use a title such as `Lab 01 — Your Name`. In the description include:

- your name and lab number;
- a short description of the completed tasks;
- the path to your completed `report.md`;
- any remaining problems or questions.

Mark the PR ready for review. With CODEOWNERS configured, GitHub requests the
instructor's review. Send the PR URL through the submission channel specified
by the instructor. If a classroom platform or LMS is used, submit that same
URL there; this document remains the source of the Git workflow instructions.

## 5. Address feedback and merge after approval

The instructor reviews the code and report and chooses **Request changes** or
**Approve**. Respond to comments and commit fixes to the same lab branch. Push
them to update the existing PR; do not open another PR for each correction.
Request another review after pushing fixes.

After the instructor approves the current changes and all required checks pass,
merge the PR into your fork's `master`. Keep the PR as the record of the review.
Then update your local clone before starting the next lab:

```bash
git checkout master
git pull --ff-only origin master
```

Run these commands with your current work committed and your working tree
clean. Instructor approval records acceptance of the reviewed work; later
changes require another review.

## 6. Receive new labs from the instructor

New labs added to the instructor's repository do not appear in your fork
automatically. Bring them in on a separate update branch so your protected
`master` still follows the PR workflow.

For example, when Lab 03 is published, run from the root of your clone with a
clean working tree:

```bash
git checkout master
git pull --ff-only origin master
git checkout -b update-course-lab03
git fetch upstream
git merge upstream/master
```

If there are conflicts, resolve them while preserving your completed work,
stage only the resolved files, and run `git commit` to finish the merge. Ask the
instructor if you are unsure which version to keep. Then push:

```bash
git push -u origin update-course-lab03
```

Open a PR from `update-course-lab03` to `master` in your own fork and request
instructor approval. After it is approved and merged, update local `master`
with `git pull --ff-only origin master`, then create your `lab03` work branch.
Use a new update-branch name for each later course update.
