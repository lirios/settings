pipeline {
  agent {
    docker {
      image "fedora:30"
      args '--user root'
    }
  }
  environment {
    CI = 1
    TX_TOKEN = credentials('transifex-token')
  }
  stages {
    stage('Translations') {
      steps {
        sh label: 'Installation', script: '''dnf install -y git transifex-client qt5-linguist binutils
strip --remove-section=.note.ABI-tag /usr/lib64/libQt5Core.so.5
curl -o /usr/bin/transifex-push https://raw.githubusercontent.com/lirios/repotools/develop/translations/transifex-push && chmod 755 /usr/bin/transifex-push
curl -o /usr/bin/transifex-pull https://raw.githubusercontent.com/lirios/repotools/develop/translations/transifex-pull && chmod 755 /usr/bin/transifex-pull
curl -o /usr/bin/translate-desktop https://raw.githubusercontent.com/lirios/repotools/develop/translations/translate-desktop && chmod 755 /usr/bin/translate-desktop'''
        sh label: 'Update translations', script: '/usr/bin/transifex-push . && /usr/bin/transifex-pull .'
      }
    }
  }
}
