# Maintainer: Peter Mount <peter@retep.org>

pkgname="libarea51-rest"
pkgver="0.2"
pkgrel="3"
pkgdesc="Area51 HTTP Rest server"
arch="x86_64"
url="https://area51.onl/"
license="ASL 2.0"
source=""
subpackages="$pkgname-dev"
depends="libarea51-httpd libarea51 json-c libmicrohttpd"
depends_dev="libarea51-httpd-dev libarea51-dev json-c-dev libmicrohttpd-dev"
#triggers="$pkgname-bin.trigger=/lib:/usr/lib:/usr/glibc-compat/lib"

builddeps() {
  sudo apk add $depends $depends_dev
}

package() {
  autoconf
  ./configure
  make clean
  make -j1
  mkdir -p "$pkgdir/usr/lib"
  cp -rp build/package/usr/lib/* "$pkgdir/usr/lib"
}

#  depends="$pkgname libarea51-rest"
dev() {
  mkdir -p "$subpkgdir/usr/include"
  cp -rp build/package/usr/include/* "$subpkgdir/usr/include"
}
