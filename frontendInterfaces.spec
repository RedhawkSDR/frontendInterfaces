#
# This file is protected by Copyright. Please refer to the COPYRIGHT file 
# distributed with this source distribution.
# 
# This file is part of REDHAWK core.
# 
# REDHAWK core is free software: you can redistribute it and/or modify it under 
# the terms of the GNU Lesser General Public License as published by the Free 
# Software Foundation, either version 3 of the License, or (at your option) any 
# later version.
# 
# REDHAWK core is distributed in the hope that it will be useful, but WITHOUT 
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS 
# FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
# details.
# 
# You should have received a copy of the GNU Lesser General Public License 
# along with this program.  If not, see http://www.gnu.org/licenses/.
#

# By default, the RPM will install to the standard REDHAWK OSSIE root location (/usr/local/redhawk/core)
%{!?_ossiehome: %define _ossiehome /usr/local/redhawk/core}
%define _prefix %{_ossiehome}
Prefix: %{_prefix}

# Point install paths to locations within our target OSSIE root
%define _sysconfdir    %{_prefix}/etc
%define _localstatedir %{_prefix}/var
%define _mandir        %{_prefix}/man
%define _infodir       %{_prefix}/info

# Assume Java support by default. Use "rpmbuild --without java" to disable, or define RPM variable "_without_java"
%{!?_with_java: %{!?_without_java: %define _with_java 1}}

Summary: The frontend library for REDHAWK
Name: frontendInterfaces
Version: 2.0.1
Release: 1.%{?dist}
License: None
Group: REDHAWK/Interfaces
Source: %{name}-%{version}.tar.gz 
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-buildroot
Requires: redhawk >= 1.8
Requires: bulkioInterfaces >= 1.8
BuildRequires: redhawk >= 1.8
BuildRequires: bulkioInterfaces >= 1.8
BuildRequires: autoconf automake libtool
BuildRequires: omniORB
BuildRequires: python omniORBpy omniORBpy-devel
%{?_with_java:BuildRequires: jdk}

%description
Libraries and interface definitions for frontend.

%prep
%setup

%build
# Explicitly set JAVA_HOME and add to PATH (for idlj)
export JAVA_HOME=/usr/java/default
export PATH=${JAVA_HOME}/bin:${PATH}
./reconf
%configure %{?_without_java: --disable-java}
make

%install
rm -rf --preserve-root $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT

%clean
rm -rf --preserve-root $RPM_BUILD_ROOT

%files
%defattr(-,redhawk,redhawk)
%{_datadir}/idl/redhawk/FRONTEND
%{_includedir}/redhawk/FRONTEND
%{_libdir}/libfrontendInterfaces.*
%{_libdir}/pkgconfig/frontendInterfaces.pc
%{_prefix}/lib/python/redhawk/frontendInterfaces
%if %{?_with_java:1}%{!?_with_java:0}
%{_prefix}/lib/FRONTENDInterfaces.jar
%{_prefix}/lib/FRONTENDInterfaces.src.jar
%endif
%if "%{?rhel}" == "6"
%{_prefix}/lib/python/%{name}-0.0.0-py2.6.egg-info
%endif

%post
/sbin/ldconfig

%postun
/sbin/ldconfig
