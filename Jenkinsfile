pipeline {
  triggers {
    cron '''TZ=Europe/Rome
H H * * *'''
  }
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
        sh label: 'Installation', script: '''dnf install -y git transifex-client qt5-linguist
strip --remove-section=.note.ABI-tag /usr/lib64/libQt5Core.so.5
curl -O https://raw.githubusercontent.com/lirios/repotools/develop/translations/transifex-push && chmod 755 transifex-push
curl -O https://raw.githubusercontent.com/lirios/repotools/develop/translations/transifex-pull && chmod 755 transifex-pull
curl -O https://raw.githubusercontent.com/lirios/repotools/develop/translations/translate-desktop && chmod 755 translate-desktop'''
        sh label: 'Prepare', script: "git branch --set-upstream-to origin/${env.GIT_BRANCH}"
        sh label: 'Update translations', script: './transifex-push . && ./transifex-pull .'
        sh label: 'Cleanup', script: 'rm -f transifex-{push,pull}'
      }
    }
  }
}
