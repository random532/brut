# $FreeBSD$

PORTNAME=	xdisk
DISTVERSION=	1.0
CATEGORIES=	sysutils
MASTER_SITES=	https://raw.githubusercontent.com/random532/partition-editor-FreeBSD/master/port/
MAINTAINER=	georg.lastname@web.de
COMMENT=	Partition Editor with GUI (x11), create file systems, write .iso

LICENSE=	BSD2CLAUSE
USES=		gnome xorg motif
USE_XORG=	x11 xt
USE_MOTIF=	xm
USE_GNOME=	atk cairo gconf2 gdkpixbuf2 glib20 gtk30 pango
RUN_DEPENDS=	${LOCALBASE}/sbin/mkntfs:sysutils/fusefs-ntfs

do-install:
	${INSTALL_PROGRAM} -g wheel -m 0755 -o root work/${PORTNAME}-${DISTVERSION}/${PORTNAME} ${STAGEDIR}/${LOCALBASE}/bin

post-install:
	dbus-uuidgen --ensure

.include <bsd.port.mk>
