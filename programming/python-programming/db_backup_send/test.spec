Name:           test
Version:        1.0
Release:        0
Summary:        Simple test 
Group:          Applications/Multimedia
License:        GPL
URL:            http://www.icecast.org/
Vendor:         Xiph.org Foundation team@icecast.org
Source:         /root/rpmbuild/SOURCES/test-1.0.tar.gz 
Prefix:         %{_prefix}
Packager: 	Somnath
BuildRoot:      %{_tmppath}/%{name}-root

%description
This is test sample.

%prep
echo "---------prepare---------"
echo "%setup -q -n %{name}-%{version}"

%build
echo "-----build--------"
echo "$RPM_BUILD_ROOT"
mkdir -p $RPM_BUILD_ROOT
tar -zxvf /root/rpmbuild/SOURCES/test-1.0.tar.gz -C $RPM_BUILD_ROOT


%install
echo "---------install----------"

%clean
echo "----------------clean-----------------------"

%files
/test-1.0/test.sh
/test-1.0/README


