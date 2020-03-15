# $FreeBSD$

PORTNAME=	xdisk
DISTVERSION=	1.0
CATEGORIES=	sysutils
MASTER_SITES=	https://raw.githubusercontent.com/random532/xdisk---FreeBSD-Partition-Editor/master/port/

MAINTAINER=	georg.lastname@web.de
COMMENT=	GUI for editing hard drives (partition editor), uses X11, gtk3

LICENSE=	BSD2CLAUSE

USES=		gnome
USE_GNOME=	atk cairo gconf2 gdkpixbuf2 glib20 gtk30 pango

do-install:
	${INSTALL_PROGRAM} -g wheel -m 0755 -o root work/${PORTNAME}-${DISTVERSION}/${PORTNAME} ${STAGEDIR}/${LOCALBASE}/bin

.include <bsd.port.mk>
