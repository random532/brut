# $FreeBSD$

PORTNAME=	xdisk
DISTVERSION=	1.0
CATEGORIES=	sysutils
MASTER_SITES=	https://raw.githubusercontent.com/random532/partition-editor-FreeBSD/master/port/
MAINTAINER=	georg.lastname@web.de
COMMENT=	a GUI for editing hard drives (partition editor, disk editor, X11, gtk3)

LICENSE=	BSD2CLAUSE
USES=		gnome xorg
USE_XORG=	x11 xt
USE_GNOME=	atk cairo gconf2 gdkpixbuf2 glib20 gtk30 pango

do-install:
	${INSTALL_PROGRAM} -g wheel -m 0755 -o root work/${PORTNAME}-${DISTVERSION}/${PORTNAME} ${STAGEDIR}/${LOCALBASE}/bin

.include <bsd.port.mk>
