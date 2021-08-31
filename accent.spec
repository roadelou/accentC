Name: accent
Version: 1.0
Release: 1%{?dist}
Summary: accent is a simple CLI tool to add french accents to a text file using markup

License: GPLv3
URL: https://github.com/roadelou/accentC

BuildRequires: gcc
BuildRequires: make

%description
accent is a simple CLI tool to add french accents to a text file using markup.

%prep
# No preparation is needed here, we are already inside of the source code.

%build
# We just call `make [all]` to compile the executable.
make %{?_smp_mflags}

%install
# `make install` is used to install the executable.
%make_install

%files
# This section is used to specify which files this package creates.
#
# This is the executable itself, stored in /usr/bin
/usr/bin/accent
