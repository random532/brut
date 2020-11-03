# $FreeBSD$

PORTNAME=	brut
DISTVERSION=	1.49
CATEGORIES=	sysutils

MAINTAINER=	georg.lastname@web.de
COMMENT=	Multitool, Partition Editor, Manage Groups/User

LICENSE=	BSD2CLAUSE

RUN_DEPENDS=	sudo>0:security/sudo

USES=		gnome
USE_GNOME=	gtk30

USE_GITHUB=	yes
GH_ACCOUNT=	random532

PLIST_FILES=	bin/brut

do-install:
	${INSTALL_PROGRAM} work/${PORTNAME}-${DISTVERSION}/${PORTNAME} ${STAGEDIR}${LOCALBASE}/bin

.include <bsd.port.mk>
