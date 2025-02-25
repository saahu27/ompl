# Download {#download}

## Releases

- __OMPL.app__ 1.6.0, released Feb 19, 2025 ([release notes](releaseNotes.html)):

  <a href="https://github.com/ompl/omplapp/releases/download/1.6.0/omplapp-1.6.0-Source.tar.gz
" class="btn btn-primary btn-sm">TGZ</a>
  <a href="https://github.com/ompl/omplapp/releases/download/1.6.0/omplapp-1.6.0-Source.zip
" class="btn btn-primary btn-sm">ZIP</a>

- __OMPL__ 1.6.0, released Feb 19, 2025 ([release notes](core/releaseNotes.html)):

  Just the [core OMPL library](/core/download.html) (no GUI, no bindings to [FCL](http://gamma.cs.unc.edu/FCL), [PQP](http://gamma.cs.unc.edu/SSV), and [Assimp](http://assimp.sf.net)):

  <a href="https://github.com/ompl/ompl/archive/1.6.0.tar.gz
" class="btn btn-primary btn-sm">TGZ</a>
  <a href="https://github.com/ompl/ompl/archive/1.6.0.zip
" class="btn btn-primary btn-sm">ZIP</a>

  OMPL is also available through through several package managers:
  - [Debian](https://packages.debian.org/sid/libompl-dev),
  - [Ubuntu (14.04 and higher)](http://packages.ubuntu.com/search?keywords=libompl-dev),
  - [Fedora](https://apps.fedoraproject.org/packages/ompl),
  - [MacPorts](https://www.macports.org),
  - [Homebrew](http://brew.sh), and
  - [vcpkg](https://vcpkg.readthedocs.io).
  .
  Note that these package managers may not always have the latest release.

- [Installation script for Ubuntu 16.04 and higher](install-ompl-ubuntu.sh)
- [Installation instructions.](installation.html)
- [Older releases](https://github.com/ompl/omplapp/releases). See the [release notes](core/releaseNotes.html) for a brief a description of changes for each release.

## Repositories {#download_repos}

- The latest source of [OMPL.app](https://github.com/ompl/omplapp) and [OMPL](https://github.com/ompl/ompl) are available on GitHub. The OMPL.app repository contains the OMPL repository as a submodule. You can clone both at the same time like so:

      git clone --recurse-submodules https://github.com/ompl/omplapp.git

  If you are only interested in the OMPL code, clone just the OMPL repository like so:

      git clone https://github.com/ompl/ompl.git

- [Installation instructions](installation.html) are the same as for a release.
