# Contribution Guidelines

STM8 eForth is a community project, and contributions are highly appreciated!

Here are some guidelines for contributing:

* Of course there are bugs, and we hate them. If you find one, please file an issue! If you can fix it, please make a pull request!
* The same goes for less-than-acceptable grammar, or wrong/outdated contents in the docs. Please propose how to improve it (e.g. using a [Gist](https://gist.github.com/)).
* Please check the issues to see if there's anything related to your contribution. Feel free to comment on closed issues if you feel that the root cause has not been fixed.
* If you're looking for things to work on please check for [open issues](https://github.com/TG9541/stm8ef/issues), or for cards in the project [boards](https://github.com/TG9541/stm8ef/projects)!
* If you need a new feature that you think would be an improvement please also file an issue. Describe what you need, why you need it, and the acceptance criteria of a solution.

## Pull Requests

* Please fork the repository.
* Make your changes in a well-named topic branch.
* Submit your pull request. Please [reference an issue](https://help.github.com/articles/closing-issues-using-keywords/) (i.e. `resolves #..` ) if it's related to one.

## Coding Style

General:
* please use Unix line endings,
* avoid trailing whitespace,
* and don't use tabs

For Forth code please use [Brodie style](http://www.forth.org/forth_style.html):
* after colon: 1 space
* after a defined name: 2 space
* after stack comment: 2 space (or newline)
* separate phrases on same line: 3 spaces
* indent: 3 spaces
* keep lines shorter than 64 characters
* use the `mcu/`, and the `lib/` folders (subset of the e4thcom search path)

For assembly code, please use the following formatting:
* keep lines shorter than 80 characters
* use upper case mnemonics
* line comments: semicolon as the first character, start of comment in column 8
* in-line comments: try to place the semicolon on column 34

## Licensing & Legal Stuff

Please don't contribute code that doesn't fit our [ISC](https://en.wikipedia.org/wiki/ISC_license) style license. 
If the code isn't yours, or if you don't have the original authors permission to use it under the terms of the license, then please don't put it in a pull request!
