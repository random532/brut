# $FreeBSD$

PORTNAME=	xdisk
DISTVERSION=	1.39
CATEGORIES=	sysutils

MAINTAINER=	georg.lastname@web.de
COMMENT=	Disk editor, partition editor with graphical user interface

LICENSE=	BSD2CLAUSE

RUN_DEPENDS=	sudo>0:security/sudo

USES=		gnome
USE_GNOME=	gtk30

USE_GITHUB=	yes
GH_ACCOUNT=	random532

PLIST_FILES=	bin/xdisk

do-install:
	${INSTALL_PROGRAM} work/${PORTNAME}-${DISTVERSION}/${PORTNAME} ${STAGEDIR}${LOCALBASE}/bin

.include <bsd.port.mk>
