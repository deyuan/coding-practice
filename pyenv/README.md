# Python Environment Setup

## Recommended Solution
* Do not touch any default Python installation in the OS
* Use `pyenv` to manage and isolate differnet Python versions
* Use `pyenv-virtualenv` to manage and isolate project specific package dependencies
* Allow `pip` to install in virtual environment only

This can ensure a clean Python development environment.

## Links
Follow the instructions on installation and shell setup:
* `pyenv`: https://github.com/pyenv/pyenv
* `pyenv-virtualenv`: https://github.com/pyenv/pyenv-virtualenv

Set this in shell rc to avoid messing up non-virtual environments:
* `export PIP_REQUIRE_VIRTUALENV=true`
* https://docs.python-guide.org/dev/pip-virtualenv

## Usage Model
How to use pyenv:
* `pyenv install --list`: List available Python versions
* `pyenv install <version>`: Install a Python version
* `pyenv version`: Show current Python version
* `pyenv versions`: Show all installed Python versions
* `pyenv global <version>`: Switch to a version globally
* `pyenv shell <version>`: Switch to a version in current shell
* `pyenv local <version>`: Switch to a version in current directory

How to use pyenv-virtualenv:
* `pyenv virtualenv <name>`: Create a virtual environment
* `pyenv virtualenv <version> <name>`: Create a virtual environment with a specific Python version
* `pyenv virtualenv-delete <name>`: Delete a virtual environment
* `pyenv virtualenvs`: List all virtual environments
* `pyenv activate`: Activate a virtual environment
* `pyenv deactivate`: Deactivate a virtual environment

How to install packages within an activated virtual environment:
* `pip install <package>`

For each project:
* Install a specific Python version if needed
* Create a project specific virtual environment
* Install any dependent packages within the virtual environment

