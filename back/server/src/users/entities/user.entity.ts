import { Ban } from 'src/ban/entities/ban.entity';
import { Friend } from 'src/friend/entities/friend.entity';
import { Match } from 'src/match/entities/match.entity';
import { Stat } from 'src/stats/entities/stat.entity';
import { Column, Entity, OneToMany, OneToOne, PrimaryColumn } from 'typeorm';

@Entity('users')
export class User {
  @PrimaryColumn()
  intra_id: string;

  @Column()
  nickname: string;

  @Column()
  intra_email: string;

  @Column()
  avatar: string;

  @Column()
  status: string;

  @Column()
  channel_id: string;

  @Column({ default: null })
  socket_id: string | null;

  @Column({ default: false })
  is_second_auth: boolean;

  @Column({ default: false })
  enable2fa?: boolean;

  @OneToOne(() => Stat, (stat) => stat.user, {
    cascade: ['remove', 'insert', 'update'],
  })
  stats: Stat;

  @OneToMany(() => Match, (match) => match.player_1, { nullable: true })
  matches_1?: Match[];

  @OneToMany(() => Match, (match) => match.player_2, { nullable: true })
  matches_2?: Match[];

  @OneToMany(() => Friend, (friend) => friend.friend_1, { nullable: true })
  friend_1?: Friend[];

  @OneToMany(() => Friend, (friend) => friend.friend_2, { nullable: true })
  friend_2?: Friend[];

  @OneToMany(() => Ban, (ban) => ban.ban_1, { nullable: true })
  ban_1?: Ban[];

  @OneToMany(() => Ban, (ban) => ban.ban_2, { nullable: true })
  ban_2?: Ban[];
}
